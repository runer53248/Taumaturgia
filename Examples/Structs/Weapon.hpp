#pragma once
#include "Usage/Types/Damage/Damage.hpp"
#include "Usage/Types/Name/Name.hpp"

#ifdef WITH_ADD_PROPERTIES
#include "EmptyType.hpp"
using Weapon = add_properties<
    Type,
    Naming,
    Damaging>;
#else

// struct Weapon {
//     Name name;
//     Damage dmg{};
// };

class Weapon {
public:
    Name name;

    Weapon() noexcept = default;
    Weapon(const Name& name) noexcept
        : name{name} {}
    Weapon(const Name& name, Damage dmg) noexcept
        : name{name}, dmg{dmg} {}

    auto& Dmg() noexcept {
        return dmg;
    }

    const auto& Dmg() const noexcept {
        return dmg;
    }

private:
    Damage dmg{};
};

template <typename T>
    requires std::is_base_of_v<Weapon, T>
struct traits::CustomAccessDamage<T> {
    static constexpr decltype(auto) get(auto& el) {
        return el.Dmg();
    }
};

#endif
