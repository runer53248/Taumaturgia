#pragma once
#include "EmptyType.hpp"
#include "Usage/Types/Damage/Damage.hpp"
#include "Usage/Types/Name/Name.hpp"

using WeaponBuild = add_properties_ordered<
    Type,
    Naming,
    Damaging>;

// struct WeaponClass {
//     Name name;
//     Damage dmg{};
// };

class WeaponClass {
public:
    WeaponClass() noexcept = default;
    WeaponClass(const Name& name) noexcept
        : name{name} {}
    WeaponClass(const Name& name, Damage dmg) noexcept
        : name{name}, dmg{dmg} {}

    auto& Dmg() noexcept {
        return dmg;
    }

    const auto& Dmg() const noexcept {
        return dmg;
    }

    Name name;

private:
    Damage dmg{};
};

template <typename T>
    requires std::is_base_of_v<WeaponClass, T>
struct traits::CustomAccessType<Damage, T> {
    static constexpr decltype(auto) get(auto& el) {
        return el.Dmg();
    }
};

#ifdef WITH_ADD_PROPERTIES
using Weapon = WeaponBuild;
#else
using Weapon = WeaponClass;
#endif
