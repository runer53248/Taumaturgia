#pragma once
#include "EmptyType.hpp"
#include "Usage/Types/Damage/Damage.hpp"

using NoNameWeaponBuild = add_properties_ordered<
    Type,
    Damaging>;

struct NoNameWeaponClass {
    Damage dmg{};
};

#ifdef WITH_ADD_PROPERTIES
using NoNameWeapon = NoNameWeaponBuild;
#else
using NoNameWeapon = NoNameWeaponClass;
#endif
