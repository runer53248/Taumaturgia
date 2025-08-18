#include <iostream>
#include <string>
#include "Examples/Checks.hpp"
#include "Usage/Traits.hpp"
#include "Usage/Types/Name/Name.hpp"

constexpr auto default_name = "Valid";

// Namingable concepts is valid for types that:
// * type that have public getName method returning std::string convertible type

struct t_empty {};

// MARK: t_getName_property

template <typename T, typename TYPE>
class t_getName_property : public T {
public:
    t_getName_property() = default;
    explicit t_getName_property(const TYPE& name)
        : name{name} {}

    TYPE& getName() & {
        return name;
    }

    const TYPE& getName() const& {
        return name;
    }

private:
    TYPE name{default_name};
};
static_assert(Namingable<t_getName_property<t_empty, const char*>>);
static_assert(Namingable<t_getName_property<t_empty, std::string>>);
static_assert(Namingable<t_getName_property<t_empty, Name>>);

auto& operator<<(std::ostream& out, const Name& name) {
    return out << static_cast<std::string>(name);
}

// MARK: main

int main() {
    auto type4_1 = t_getName_property<t_empty, const char*>{"t_getName_simple"};
    auto type4_2 = t_getName_property<t_empty, std::string>{"t_getName_string"};
    auto type4_3 = t_getName_property<t_empty, Name>{Name{"t_getName_Name"}};

    std::cout << '\n';
    std::cout << "Take name from by access trait:" << '\n';
    std::cout << "trait<Name>::get(type4_1) = " << trait<Name>::get(type4_1) << '\n';
    std::cout << "trait<Name>::get(type4_2) = " << trait<Name>::get(type4_2) << '\n';
    std::cout << "trait<Name>::get(type4_3) = " << trait<Name>::get(type4_3) << '\n';
    {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
