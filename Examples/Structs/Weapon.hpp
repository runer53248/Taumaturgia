#pragma once
#include "Taumaturgia/Types/Damage.hpp"
#include "Taumaturgia/Types/Name.hpp"

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
    static decltype(auto) get(auto& el) {
        return el.Dmg();
    }
};
