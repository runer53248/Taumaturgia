#include <iostream>
#include "Examples/Checks.hpp"
#include "Taumaturgia/Object/Enums/ActionStatus.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

#include "Examples/demangle_type_name.hpp"

struct BaseType {
    // std::string name{};
};

// using Type_int = impl::UserProperty_<int, BaseType>;
using Type_int = UserProperty<int, BaseType>;

template <typename T, typename TYPE>
concept type_of = std::same_as<std::remove_const_t<T>, TYPE>;

template <typename TYPE>
struct traits::CustomAccessType<TYPE, Type_int> {
    static constexpr decltype(auto) get(type_of<Type_int> auto& el) {
        if consteval {
        } else {
            std::cout << name<decltype(el)>() << ' ';
            if (std::is_const_v<std::remove_reference_t<decltype(el)>>) {
                std::cout << "[const get] ";
            } else {
                std::cout << "[get] ";
            }
        }
        return el.template getType<TYPE>();
    }
};

int main() {
    Type_int type_a{/*Name{"name"},*/ 15};

    decltype(auto) x = trait<int>::get(type_a);
    std::cout << name<decltype(x)>() << ' ';
    std::cout << x << '\n';
    decltype(auto) x2 = trait<int>::get(std::as_const(type_a));
    std::cout << name<decltype(x2)>() << ' ';
    std::cout << x2 << '\n';

    std::cout << '\n';

    constexpr Type_int type_b{/*Name{"name"},*/ 15};

    decltype(auto) x3 = trait<int>::get(type_b);
    std::cout << name<decltype(x3)>() << ' ';
    std::cout << x3 << '\n';
    decltype(auto) x4 = trait<int>::get(std::as_const(type_b));
    std::cout << name<decltype(x4)>() << ' ';
    std::cout << x4 << '\n';

    static_assert(trait<int>::get(type_b) == 15);
    static_assert(trait<int>::get(std::as_const(type_b)) == 15);

    {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
