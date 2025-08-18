#include <iostream>
#include "Examples/Checks.hpp"
#include "Usage/Traits.hpp"
#include "Usage/Types/Name/Name.hpp"

constexpr auto default_name = "Valid";

// Namingable concepts is valid for types that:
// * type that have public name member convertible to std::string or const std::string

// MARK: t_Name_name

struct t_Name_name {
    Name name{default_name};
};

// MARK: t_const_Name_name

struct t_const_Name_name {
    const Name name{default_name};
};
static_assert(Namingable<t_Name_name>);
static_assert(Namingable<t_const_Name_name>);

auto& operator<<(std::ostream& out, const Name& name) {
    return out << static_cast<std::string>(name);
}

// MARK: main

int main() {
    auto type3a = t_Name_name{Name{"t_Name_name"}};
    auto type3b = t_const_Name_name{Name{"t_const_Name_name"}};

    std::cout << '\n';
    std::cout << "Take name from by access trait:" << '\n';
    std::cout << "trait<Name>::get(type3) = " << trait<Name>::get(type3a) << '\n';
    std::cout << "trait<Name>::get(type3) = " << trait<Name>::get(type3b) << '\n';
    {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
