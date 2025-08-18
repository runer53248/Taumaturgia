#include <iostream>
#include <string>
#include "Examples/Checks.hpp"
#include "Usage/Traits.hpp"
#include "Usage/Types/Name/Name.hpp"

#include "Usage/Premade/Properties/Naming.hpp"

constexpr auto default_name = "Valid";

struct t_simple_name {
    const char* name{default_name};
};
struct t_string_name {
    std::string name{default_name};
};
struct t_Name_name {
    Name name{default_name};
};

// Namingable concepts is valid for types that:
// * type resulted after gived Naming Properties

struct t_empty {};

// MARK: t_Naming_t_empty

using t_Naming_t_empty = Naming<t_empty>;
using t_Naming_t_simple_name = Naming<t_simple_name>;
using t_Naming_t_string_name = Naming<t_string_name>;
using t_Naming_t_Name_name = Naming<t_Name_name>;

static_assert(not Namingable<t_empty>);
static_assert(Namingable<t_simple_name>);
static_assert(Namingable<t_string_name>);
static_assert(Namingable<t_Name_name>);

// Naming property is not propagated if type is already Namingable
static_assert(not std::is_same_v<t_Naming_t_empty, t_empty>);
static_assert(std::is_same_v<t_Naming_t_simple_name, t_simple_name>);
static_assert(std::is_same_v<t_Naming_t_string_name, t_string_name>);
static_assert(std::is_same_v<t_Naming_t_Name_name, t_Name_name>);

auto& operator<<(std::ostream& out, const Name& name) {
    return out << static_cast<std::string>(name);
}

// MARK: main

int main() {
    auto type5a = t_Naming_t_empty{Name{"t_Naming_t_empty"}};
    auto type5b = t_Naming_t_simple_name{"t_Naming_t_simple_name"};
    auto type5c = t_Naming_t_string_name{"t_Naming_t_string_name"};
    auto type5d = t_Naming_t_Name_name{Name{"t_Naming_t_Name_name"}};

    std::cout << '\n';
    std::cout << "Take name from by access trait:" << '\n';
    std::cout << "trait<Name>::get(type5a) = " << trait<Name>::get(type5a) << '\n';
    std::cout << "trait<Name>::get(type5b) = " << trait<Name>::get(type5b) << '\n';
    std::cout << "trait<Name>::get(type5c) = " << trait<Name>::get(type5c) << '\n';
    std::cout << "trait<Name>::get(type5d) = " << trait<Name>::get(type5d) << '\n';
    {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
