#pragma once
#include "Taumaturgia/Types/Name.hpp"

#ifdef WITH_ADD_PROPERTIES
#include "EmptyType.hpp"
using Potion = add_properties<Type, Naming>;
#else

struct Potion {
    Name name;
};

#endif
