#include <iostream>
#include "Usage/Traits.hpp"

constexpr auto default_name = "Valid";

// Namingable concepts is valid for types that:
// * type that have public name member convertible to std::string or const std::string

// MARK: t_simple_name

struct t_simple_name {
    const char* name{default_name};
};
static_assert(Namingable<t_simple_name>);

// MARK: main

int main() {
    auto type1 = t_simple_name{"t_simple_name"};

    std::cout << '\n';
    std::cout << "Take name from member:" << '\n';
    std::cout << "type1.name = " << type1.name << '\n';

    std::cout << '\n';
    std::cout << "Take name from by access trait:" << '\n';
    std::cout << "trait<Name>::get(type1) = " << trait<Name>::get(type1) << '\n';
    return 0;
}
