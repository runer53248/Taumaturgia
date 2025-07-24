#pragma once

// MARK: Weapon_C

class Weapon_C {
public:
    std::string name;

    Weapon_C(const std::string& name, Damage dmg)
        : name{name}, dmg{dmg} {}

    auto& Dmg() { return dmg; }
    const auto& Dmg() const { return dmg; }

private:
    Damage dmg;
};

// MARK: traits::CustomAccessType<Damage, Weapon_C>

template <typename T>
    requires std::is_base_of_v<Weapon_C, T>
struct traits::CustomAccessType<Damage, T> {
    static constexpr decltype(auto) get(auto& el) {
        return el.Dmg();
    }
};
