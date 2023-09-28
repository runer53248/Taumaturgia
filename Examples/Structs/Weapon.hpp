#pragma once
#include "Object/Concepts/Types/Damage.hpp"
#include "Object/Concepts/Types/Name.hpp"

// struct Weapon {
//     Name name;
//     Damage dmg{};
// };

struct Weapon {
    Name name;

    Weapon() = default;
    Weapon(const Name& name)
        : name{name} {}
    Weapon(const Name& name, Damage dmg)
        : name{name}, dmg{dmg} {}

    ~Weapon() = default;

    auto& Dmg() {
        return dmg;
    }

    const auto& Dmg() const {
        return dmg;
    }

private:
    Damage dmg{};
};

template <typename T>
    requires std::is_base_of_v<Weapon, T>
struct traits::CustomAccessDamage<T> {
    static auto& get(auto& el) {
        return el.Dmg();
    }
};
