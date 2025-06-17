#include <iostream>
#include "Usage/Traits.hpp"
#include "Usage/Types/Name/Name.hpp"

#include "Usage/Premade/Properties/Naming.hpp"

// Namingable concepts is valid for types that:
// * type that have CustomAccessName trait specialization
// TODO: check CustomAccessType vs CustomAccessName

// MARK: t_custom_name

struct t_custom_name {
    auto name() & { return Name{"t_custom_name"}; }
    auto name() const& { return Name{"const t_custom_name"}; }
};

template <typename T>
    requires std::is_base_of_v<t_custom_name, T>
struct traits::CustomAccessType<Name, T> {
    static constexpr decltype(auto) get(auto& el) {
        return el.name();
    }
};
static_assert(Namingable<t_custom_name>);
static_assert(std::is_same_v<Naming<t_custom_name>, t_custom_name>);

auto& operator<<(std::ostream& out, const Name& name) {
    return out << static_cast<std::string>(name);
}

// MARK: main

int main() {
    auto type6 = t_custom_name{};

    std::cout << '\n';
    std::cout << "Take name from by access trait:" << '\n';
    std::cout << "trait<Name>::get(type6) = " << trait<Name>::get(type6) << '\n';
    std::cout << "trait<Name>::get(std::as_const(type6)) = " << trait<Name>::get(std::as_const(type6)) << '\n';
    return 0;
}
