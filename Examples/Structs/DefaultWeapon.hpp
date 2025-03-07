#pragma once
#include <string>
#include "EmptyType.hpp"
#include "Usage/Types/Damage/Damage.hpp"

using DefaultWeaponBuild = add_properties_ordered<
    Type,
    Naming,
    Damaging>;

struct DefaultWeaponClass {
    std::string name;  // string used as name
    Damage dmg{};
};

#ifdef WITH_ADD_PROPERTIES
using DefaultWeapon = DefaultWeaponBuild;
#else
using DefaultWeapon = DefaultWeaponClass;
#endif
