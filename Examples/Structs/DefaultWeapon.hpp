#pragma once
#include <string>
#include "Usage/Types/Damage.hpp"

#ifdef WITH_ADD_PROPERTIES
struct EmptyType {};
using DefaultWeapon = add_properties<EmptyType, Naming, Damaging>;
#else

struct DefaultWeapon {
    std::string name;  // string used as name
    Damage dmg{};
};

#endif
