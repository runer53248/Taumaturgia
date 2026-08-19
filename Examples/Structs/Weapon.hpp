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

    //* for parse_type_name function to deduce types

    template <size_t S = 0, typename Self>
        requires(S < 2)
    decltype(auto) getType(this Self&& self) {
        if constexpr (S == 0) {
            return (self.dmg);
        } else {
            return (self.name);
        }
    }

    template <size_t S = 0, typename Self>
    decltype(auto) getType(this Self&& self) = delete;

    //* alternative access 

    // template <typename T, size_t S = 0, typename Self>
    //     requires(std::same_as<T, property_t<Naming>> and S == 0)
    // decltype(auto) getType(this Self&& self) {
    //     return (self.name);
    // }
    // template <typename T, size_t S = 0, typename Self>
    //     requires(std::same_as<T, property_t<Damaging>> and S == 0)
    // decltype(auto) getType(this Self&& self) {
    //     return (self.dmg);
    // }
    // template <typename T, size_t S, typename Self>
    // decltype(auto) getType(this Self&& self) = delete;

    property_t<Naming> name{};

private:
    property_t<Damaging> dmg{};
};

template <typename T>
    requires std::is_base_of_v<WeaponClass, T>
struct traits::CustomAccessType<property_t<Damaging>, T> {
    static constexpr decltype(auto) get(auto& el) {
        return el.Dmg();
    }
};

#ifdef WITH_ADD_PROPERTIES
#define USES_ADD_PROPERTIES
using Weapon = WeaponBuild;
#else
using Weapon = WeaponClass;
#endif
