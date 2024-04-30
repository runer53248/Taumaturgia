#pragma once
#include "Taumaturgia/Types/Name.hpp"

#ifdef WITH_ADD_PROPERTIES
#include "EmptyType.hpp"
using Enemy = add_properties<Type, Naming>;
#else

struct Enemy {
    Name name;
};

#endif
