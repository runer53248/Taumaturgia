#include <iostream>
#include "Object/Properties/UserProperty.hpp"

struct MyType {
    std::string name{};
};

template <typename TYPE>
struct UserPropertyAdapter {
    template <typename T>
    using type = UserProperty<T, TYPE>;
}; 

#include "Object/Properties/Helpers/taged_list.hpp"
using order_list = taged_list<
    UserPropertyAdapter<int>::type,
    UserPropertyAdapter<std::string>::type,
    UserPropertyAdapter<float>::type  // floats have less priority
    >;                                // properties list in order
#include "Object/Properties/Helpers/Property.hpp"

template <typename T, typename TYPE>
    requires std::is_base_of_v<UserProperty_<MyType, TYPE>, T>
struct traits::CustomAccessUserType<T, TYPE> {
    static decltype(auto) get(UserProperty_<MyType, TYPE>& el) {
        return el.getType();
    }

    static decltype(auto) get(const UserProperty_<MyType, TYPE>& el) {
        return el.getType();
    }
};

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
    using UserClass = UserProperty<MyType, int>;  // just int
    UserClass user;
    static_assert(sizeof(UserClass) == sizeof(SizeTest));

    using UserClass2a = UserProperty<UserClass, float>;  // int and float
    UserClass2a user2a;
    static_assert(sizeof(UserClass2a) == sizeof(SizeTest2));

    using UserClass2b = UserProperty<MyType, float>;  // just float
    UserClass2b user2b;

    using UserClass3 = add_properties<MyType, UserPropertyAdapter<int>::type>;  // just int
    UserClass3 user3;

    using UserClass4 = add_properties<MyType, UserPropertyAdapter<float>::type, UserPropertyAdapter<int>::type>;  // int and float
    UserClass4 user4{Name{}, 5, 2.3f};
    static_assert(std::is_same_v<UserClass4, UserProperty<UserProperty<MyType, float>, int> >);

    using UserClass5 = add_properties<MyType, UserPropertyAdapter<int>::type, UserPropertyAdapter<float>::type>;  // int and float
    UserClass5 user5{Name{}, 5, 2.3f};
    static_assert(std::is_same_v<UserClass4, UserClass5>);

    const UserClass5 user5_c{Name{}, 5, 2.3f};

    decltype(auto) testF = user5.getType<float>();
    testF += 3.2f;
    decltype(auto) testF_2_c = std::as_const(user5).getType<float>();
    static_assert(std::is_same_v<decltype(testF), float&>);
    static_assert(std::is_same_v<decltype(testF_2_c), const float&>);
    std::cout << testF << '\n';

    decltype(auto) testF_c = user5_c.getType<float>();
    static_assert(std::is_same_v<decltype(testF_c), const float&>);
    std::cout << testF_c << '\n';

    auto type = user.getType();
    static_assert(std::is_same_v<decltype(type), int>);

    auto type2a = user2a.getType();
    static_assert(std::is_same_v<decltype(type2a), float>);

    auto type2b = user2b.getType();
    static_assert(std::is_same_v<decltype(type2b), float>);

    auto type3 = user3.getType();
    static_assert(std::is_same_v<decltype(type3), int>);

    auto type4 = user4.getType();
    static_assert(std::is_same_v<decltype(type4), int>);
}
