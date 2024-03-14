#include <iostream>
#include "Object/Properties/Helpers/taged_list.hpp"
#include "Object/Properties/UserProperty.hpp"

template <typename TYPE>
struct UserPropertyAdapter {
    template <typename T>
    using type = UserProperty<TYPE, T>;
};

using order_list = taged_list<
    UserPropertyAdapter<int>::type,
    UserPropertyAdapter<std::string>::type,
    UserPropertyAdapter<float>::type  // floats have less priority
    >;                                // properties list in order

#include "Object/Properties/Helpers/Property.hpp"  // depends on order_list existence

struct MyType_1 {
    std::string name{};
};

struct MyType_2 {
    std::string name{};
};

// implement CustomAccessType to replace MyType_3 most inner UserProperty type
template <typename TYPE, typename T>
    requires std::is_base_of_v<impl::UserProperty_<TYPE, MyType_2>, T>
struct traits::CustomAccessType<TYPE, T> {
    static decltype(auto) get(impl::UserProperty_<TYPE, MyType_2>& el) {
        std::cout << "get  ";
        return el.template getType<TYPE>();
    }

    static decltype(auto) get(const impl::UserProperty_<TYPE, MyType_2>& el) {
        std::cout << "const get  ";
        return el.template getType<TYPE>();
    }
};

struct MyType_3 {
    std::string name{};
};

// implement CustomAccessType to replace all MyType_3 types
template <typename TYPE, typename T>
    requires std::is_base_of_v<MyType_3, T>
struct traits::CustomAccessType<TYPE, T> {
    static decltype(auto) get(GetTypeable<TYPE> auto& el) {
        std::cout << "get2  ";
        return el.template getType<TYPE>();
    }

    static decltype(auto) get(GetTypeable<TYPE> auto const& el) {
        std::cout << "const get2  ";
        return el.template getType<TYPE>();
    }
};

template <typename TYPE>
void UserStrategy_<TYPE, Default>::operator()(Typeable<TYPE> auto& obj) const {
    std::cout << "UserStrategy_ call \n";
    decltype(auto) value = traits::accessType<TYPE>::get(obj);
    std::cout << value << '\n'
              << '\n';
    return;
}

struct SizeTest {
    std::string name{};
    int type;
};

struct SizeTest2 {
    std::string name{};
    int type;
    float type2;
};

int main() {
    using UserClass = UserProperty<int, MyType_1>;  // just int
    UserClass user;
    static_assert(sizeof(UserClass) == sizeof(SizeTest));
    auto type = user.getType<int>();
    static_assert(std::is_same_v<decltype(type), int>);

    using UserClass2a = UserProperty<float, UserClass>;  // int and float
    UserClass2a user2a;
    static_assert(sizeof(UserClass2a) == sizeof(SizeTest2));
    auto type2a = user2a.getType<float>();
    static_assert(std::is_same_v<decltype(type2a), float>);

    using UserClass2b = UserProperty<float, MyType_1>;  // just float
    UserClass2b user2b;
    auto type2b = user2b.getType<float>();
    static_assert(std::is_same_v<decltype(type2b), float>);

    using UserClass3 = add_properties<MyType_1, UserPropertyAdapter<int>::type>;  // just int
    UserClass3 user3;
    auto type3 = user3.getType<int>();
    static_assert(std::is_same_v<decltype(type3), int>);

    using UserClass4 = add_properties<MyType_1, UserPropertyAdapter<float>::type, UserPropertyAdapter<int>::type>;  // int and float
    UserClass4 user4{Name{}, 5, 2.3f};
    static_assert(std::is_same_v<UserClass4, UserProperty<int, UserProperty<float, MyType_1>>>);
    auto type4 = user4.getType<int>();
    static_assert(std::is_same_v<decltype(type4), int>);

    using UserClass5 = add_properties<MyType_1, UserPropertyAdapter<int>::type, UserPropertyAdapter<float>::type>;  // int and float
    static_assert(std::is_same_v<UserClass4, UserClass5>);

    const UserClass5 user5_c{Name{}, 21, 3.14159f};
    decltype(auto) testI_c = user5_c.getType<int>();
    decltype(auto) testF_c = user5_c.getType<float>();
    static_assert(std::is_same_v<decltype(testF_c), const float&>);
    std::cout << testI_c << '\n';
    std::cout << testF_c << '\n'
              << '\n';

    UserClass5 user5{Name{}, 5, 2.3f};
    // [[maybe_unused]] decltype(auto) testDefault = user5.getType();  // int
    decltype(auto) testF = user5.getType<float>();
    static_assert(std::is_same_v<decltype(testF), float&>);
    decltype(auto) testI = user5.getType<int>();
    std::cout << testF << '\n';
    std::cout << testI << '\n';
    testF += 3.2f;
    testI += 1;
    decltype(auto) testF_2_c = std::as_const(user5).getType<float>();
    static_assert(std::is_same_v<decltype(testF_2_c), const float&>);
    std::cout << testF_2_c << '\n'
              << '\n';

    {
        using UserClass5_1 = add_properties<MyType_1, UserPropertyAdapter<int>::type, UserPropertyAdapter<float>::type>;
        UserClass5_1 type1{Name{}, 5, 2.3f};
        std::cout << "default trait::accessType \n";
        decltype(auto) x = traits::accessType<float>::get(std::as_const(type1));
        std::cout << x << '\n';
        decltype(auto) y = traits::accessType<float>::get(type1);
        std::cout << y << '\n';
        decltype(auto) x2 = traits::accessType<int>::get(std::as_const(type1));
        std::cout << x2 << '\n';
        decltype(auto) y2 = traits::accessType<int>::get(type1);
        std::cout << y2 << '\n'
                  << '\n';
    }

    {
        std::cout << "custom trait::accessType for one type\n";
        using UserClass5_2 = add_properties<MyType_2, UserPropertyAdapter<int>::type, UserPropertyAdapter<float>::type>;
        UserClass5_2 type2{Name{}, 5, 2.3f};
        decltype(auto) x = traits::accessType<float>::get(std::as_const(type2));
        std::cout << x << '\n';
        decltype(auto) y = traits::accessType<float>::get(type2);
        std::cout << y << '\n';
        decltype(auto) x2 = traits::accessType<int>::get(std::as_const(type2));
        std::cout << x2 << '\n';
        decltype(auto) y2 = traits::accessType<int>::get(type2);
        std::cout << y2 << '\n'
                  << '\n';
    }

    {
        std::cout << "custom trait::accessType for all types\n";
        using UserClass5_3 = add_properties<MyType_3, UserPropertyAdapter<int>::type, UserPropertyAdapter<float>::type>;
        UserClass5_3 type3{Name{}, 5, 2.3f};
        decltype(auto) x = traits::accessType<float>::get(std::as_const(type3));
        std::cout << x << '\n';
        decltype(auto) y = traits::accessType<float>::get(type3);
        std::cout << y << '\n';
        decltype(auto) x2 = traits::accessType<int>::get(std::as_const(type3));
        std::cout << x2 << '\n';
        decltype(auto) y2 = traits::accessType<int>::get(type3);
        std::cout << y2 << '\n'
                  << '\n';

        UserStrategy_<float, Default> userStrategy{};
        userStrategy(type3);
        UserStrategy_<int, Default>{}(type3);
        // UserStrategy_<std::string, Default>{}(type3);
    }
}
