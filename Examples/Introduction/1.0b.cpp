#include <iostream>
#include <string>
#include "Examples/Checks.hpp"
#include "Usage/Traits.hpp"

constexpr auto default_name = "Valid";

// Namingable concepts is valid for types that:
// * type that have public name member convertible to std::string or const std::string

// MARK: t_string_name

struct t_string_name {
    std::string name{default_name};
};

// MARK: t_const_string_name

struct t_const_string_name {
    const std::string name{default_name};
};
static_assert(Namingable<t_string_name>);
static_assert(Namingable<t_const_string_name>);

// MARK: main

int main() {
    auto type2a = t_string_name{"t_string_name"};
    auto type2b = t_const_string_name{"t_const_string_name"};

    std::cout << '\n';
    std::cout << "Take name from by access trait:" << '\n';
    std::cout << "trait<Name>::get(type2) = " << trait<Name>::get(type2a) << '\n';
    std::cout << "trait<Name>::get(type2) = " << trait<Name>::get(type2b) << '\n';
    {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
