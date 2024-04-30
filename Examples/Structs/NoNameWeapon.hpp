#pragma once
#include "Taumaturgia/Types/Damage.hpp"

#ifdef WITH_ADD_PROPERTIES
#include "EmptyType.hpp"
using NoNameWeapon = add_properties<Type, Damaging>;
#else

struct NoNameWeapon {
    Damage dmg{};
};

#endif
