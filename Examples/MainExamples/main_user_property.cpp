#include <iostream>
#include "Taumaturgia/Object/Enums/ActionStatus.hpp"
#include "Taumaturgia/Properties/Helpers/taged_list.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

using order_list = taged_list<
    UserPropertyAdapter<int>::type,
    UserPropertyAdapter<std::string>::type,
    UserPropertyAdapter<float>::type  // floats have less priority
    >;                                // properties list in order

#include "Taumaturgia/Properties/Helpers/Property.hpp"  // depends on order_list existence

struct name_type1 {
    std::string name{};
};

struct name_type2 {
    std::string name{};
};

// implement CustomAccessType to replace name_type2 most inner UserProperty type
template <typename TYPE, typename T>
    requires std::is_base_of_v<impl::UserProperty_<TYPE, name_type2>, T>
struct traits::CustomAccessType<TYPE, T> {
    static constexpr decltype(auto) get(impl::UserProperty_<TYPE, name_type2>& el) {
        if consteval {
        } else {
            std::cout << "[get] ";
        }
        return el.template getType<TYPE>();
    }

    static constexpr decltype(auto) get(const impl::UserProperty_<TYPE, name_type2>& el) {
        if consteval {
        } else {
            std::cout << "[const get] ";
        }
        return el.template getType<TYPE>();
    }
};

struct name_type3 {
    std::string name{};
};

// implement CustomAccessType to replace all name_type3 types
template <typename TYPE, typename T>
    requires std::is_base_of_v<name_type3, T>
struct traits::CustomAccessType<TYPE, T> {
    static constexpr decltype(auto) get(getType_template_able<TYPE> auto& el) {
        if consteval {
        } else {
            std::cout << "[get2] ";
        }
        return el.template getType<TYPE>();
    }

    static constexpr decltype(auto) get(getType_template_able<TYPE> auto const& el) {
        if consteval {
        } else {
            std::cout << "[const get2] ";
        }
        return el.template getType<TYPE>();
    }
};

template <typename TYPE>
constexpr ActionStatus UserStrategy_<TYPE, Default>::operator()(accessType_trait_able<TYPE> auto& obj, [[maybe_unused]] Object* owner, [[maybe_unused]] Object* target) const {
    if consteval {
        traits::accessType<TYPE>::get(obj);
    } else {
        std::cout << "UserStrategy_ call ";
        decltype(auto) value = traits::accessType<TYPE>::get(obj);
        std::cout << " = " << value << "\n";
    }
    return ActionStatus::Success;
}

struct name_int_type {
    std::string name{};
    int type;
};

struct name_int_float_type {
    std::string name{};
    int type;
    float type2;
};

struct empty {};

template <ActionStatus... STATUS>
struct ActionStatus_Assertion {
    ActionStatus_Assertion() {
        // static_assert(STATUS == ActionStatus::Success);
        static_assert(std::conjunction<std::bool_constant<(STATUS == ActionStatus::Success)>...>::value, "assertion fail");
        std::cout << "assertion success\n";
    }
};

int main() {
    using user_name_int_type = UserProperty<int, name_type1>;                  // just int
    using user_name_float_type = UserProperty<float, name_type1>;              // just float
    using user_name_int_float_type = UserProperty<float, user_name_int_type>;  // int and float
    user_name_int_type user_nit;
    user_name_float_type user_nft;
    user_name_int_float_type user_nift;
    static_assert(sizeof(user_name_int_type) == sizeof(name_int_type));

    // static_assert(sizeof(user_name_int_float_type) == sizeof(name_int_float_type));

    auto type1 = user_nit.getType<int>();
    auto type2 = user_nft.getType<float>();
    auto type3 = user_nift.getType<float>();
    auto type4 = user_nift.getType<int>();
    static_assert(std::is_same_v<decltype(type1), int>);
    static_assert(std::is_same_v<decltype(type2), float>);
    static_assert(std::is_same_v<decltype(type3), float>);
    static_assert(std::is_same_v<decltype(type4), int>);

    constexpr int value_i_1 = 5;
    constexpr int value_i_2 = 21;
    constexpr int value_i_3 = 100;

    constexpr float value_f_1 = 2.3f;
    constexpr float value_f_2 = 3.14159f;
    constexpr float value_f_3 = 6.11f;

    using user_name_a_int_type = add_properties<name_type1, UserPropertyAdapter<int>::type>;                                            // just int
    using user_name_a_float_a_int_type = add_properties<name_type1, UserPropertyAdapter<float>::type, UserPropertyAdapter<int>::type>;  // float and int
    using user_name_a_int_a_float_type = add_properties<name_type1, UserPropertyAdapter<int>::type, UserPropertyAdapter<float>::type>;  // int and float
    static_assert(std::is_same_v<user_name_a_float_a_int_type, UserProperty<int, UserProperty<float, name_type1>>>);
    static_assert(std::is_same_v<user_name_a_float_a_int_type, user_name_a_int_a_float_type>);

    user_name_a_int_type user_ai;
    auto value_i_ai = user_ai.getType<int>();
    static_assert(std::is_same_v<decltype(value_i_ai), int>);
    std::cout << value_i_ai << '\n';

    user_name_a_float_a_int_type user_afai{Name{}, value_i_1, value_f_1};
    auto value_i_afai = user_afai.getType<int>();
    auto value_f_afai = user_afai.getType<float>();
    static_assert(std::is_same_v<decltype(value_i_afai), int>);
    static_assert(std::is_same_v<decltype(value_f_afai), float>);
    std::cout << value_i_afai << '\n';
    std::cout << value_f_afai << "\n\n";

    const user_name_a_int_a_float_type c_user_naiaf{Name{}, value_i_2, value_f_2};
    decltype(auto) c_value_i_naiaf = c_user_naiaf.getType<int>();
    decltype(auto) c_value_f_naiaf = c_user_naiaf.getType<float>();
    static_assert(std::is_same_v<decltype(c_value_i_naiaf), const int&>);
    static_assert(std::is_same_v<decltype(c_value_f_naiaf), const float&>);
    std::cout << c_value_i_naiaf << '\n';
    std::cout << c_value_f_naiaf << "\n\n";

    user_name_a_int_a_float_type user_naiaf{Name{}, value_i_3, value_f_3};
    [[maybe_unused]] decltype(auto) testDefault = user_naiaf.getType<>();  // int
    decltype(auto) value_i_naiaf = user_naiaf.getType<int>();
    decltype(auto) value_f_naiaf = user_naiaf.getType<float>();
    decltype(auto) value_c_i_naiaf = std::as_const(user_naiaf).getType<int>();
    decltype(auto) value_c_f_naiaf = std::as_const(user_naiaf).getType<float>();
    static_assert(std::is_same_v<decltype(value_i_naiaf), int&>);
    static_assert(std::is_same_v<decltype(value_f_naiaf), float&>);
    static_assert(std::is_same_v<decltype(value_c_i_naiaf), const int&>);
    static_assert(std::is_same_v<decltype(value_c_f_naiaf), const float&>);
    std::cout << value_i_naiaf << '\n';
    std::cout << value_f_naiaf << "\n\n";
    value_i_naiaf += value_i_3;
    value_f_naiaf += value_f_3;
    std::cout << value_c_i_naiaf << "\n";
    std::cout << value_c_f_naiaf << "\n\n";

    {
        using UserClass5_1 = add_properties<name_type1, UserPropertyAdapter<int>::type, UserPropertyAdapter<float>::type>;
        UserClass5_1 type1{Name{}, value_i_1, value_f_1};
        std::cout << "default traits::accessType \n";
        decltype(auto) x = traits::accessType<float>::get(std::as_const(type1));
        std::cout << x << '\n';
        decltype(auto) y = traits::accessType<float>::get(type1);
        std::cout << y << '\n';
        decltype(auto) x2 = traits::accessType<int>::get(std::as_const(type1));
        std::cout << x2 << '\n';
        decltype(auto) y2 = traits::accessType<int>::get(type1);
        std::cout << y2 << '\n';
        std::cout << '\n';
    }

    {
        std::cout << "custom traits::accessType for one type\n";
        using UserClass5_2 = add_properties<name_type2, UserPropertyAdapter<int>::type, UserPropertyAdapter<float>::type>;
        UserClass5_2 type2{Name{}, value_i_2, value_f_2};
        decltype(auto) x = traits::accessType<float>::get(std::as_const(type2));
        std::cout << x << '\n';
        decltype(auto) y = traits::accessType<float>::get(type2);
        std::cout << y << '\n';
        decltype(auto) x2 = traits::accessType<int>::get(std::as_const(type2));
        std::cout << x2 << '\n';
        decltype(auto) y2 = traits::accessType<int>::get(type2);
        std::cout << y2 << '\n';
        std::cout << '\n';
    }

    {
        std::cout << "custom traits::accessType for all types\n";
        using UserClass5_3 = add_properties<name_type3, UserPropertyAdapter<int>::type, UserPropertyAdapter<float>::type>;
        UserClass5_3 type3{Name{}, value_i_3, value_f_3};
        decltype(auto) x = traits::accessType<float>::get(std::as_const(type3));
        std::cout << x << '\n';
        decltype(auto) y = traits::accessType<float>::get(type3);
        std::cout << y << '\n';
        decltype(auto) x2 = traits::accessType<int>::get(std::as_const(type3));
        std::cout << x2 << '\n';
        decltype(auto) y2 = traits::accessType<int>::get(type3);
        std::cout << y2 << '\n';
        std::cout << '\n';
    }

    {
        std::cout << "custom traits::accessType can be used both as consteval and normal\n";
        using UserClass5_3 = add_properties<name_type3, UserPropertyAdapter<int>::type, UserPropertyAdapter<float>::type>;
        UserClass5_3 type3{Name{}, value_i_3, value_f_3};

        UserStrategy_<float, Default> userStrategy{};

        userStrategy(type3, nullptr, nullptr);
        userStrategy(std::as_const(type3), nullptr, nullptr);

        UserStrategy_<int, Default>{}(type3, nullptr, nullptr);
        UserStrategy_<int, Default>{}(std::as_const(type3), nullptr, nullptr);

        std::cout << '\n';

        std::cout << "assert that result of userStrategy is ActionStatus::Success\n";
        ActionStatus_Assertion<
            userStrategy(type3, nullptr, nullptr)>{};
        ActionStatus_Assertion<
            userStrategy(std::as_const(type3), nullptr, nullptr)>{};

        ActionStatus_Assertion<
            UserStrategy_<int, Default>{}(type3, nullptr, nullptr)>{};
        ActionStatus_Assertion<
            UserStrategy_<int, Default>{}(std::as_const(type3), nullptr, nullptr)>{};

        std::cout << '\n';

        ActionStatus_Assertion<
            userStrategy(type3, nullptr, nullptr),
            userStrategy(std::as_const(type3), nullptr, nullptr),
            UserStrategy_<int, Default>{}(type3, nullptr, nullptr),
            UserStrategy_<int, Default>{}(std::as_const(type3), nullptr, nullptr)>{};
    }
}
