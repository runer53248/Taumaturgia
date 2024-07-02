#pragma once
#include <string>
#include "Usage/Types/Damage/Damage.hpp"

#ifdef WITH_ADD_PROPERTIES
#include "EmptyType.hpp"
using DefaultWeapon = add_properties<Type, Naming, Damaging>;
#else

struct DefaultWeapon {
    std::string name;  // string used as name
    Damage dmg{};
};

#endif
