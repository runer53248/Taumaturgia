#pragma once
#include "Usage/Types/Damage/Damage.hpp"

#ifdef WITH_ADD_PROPERTIES
#include "EmptyType.hpp"
using NoNameWeapon = add_properties_ordered<
    Type,
    Damaging>;
#else

struct NoNameWeapon {
    Damage dmg{};
};

#endif
