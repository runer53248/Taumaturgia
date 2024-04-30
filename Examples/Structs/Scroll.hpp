#pragma once
#include "Taumaturgia/Types/Name.hpp"

#ifdef WITH_ADD_PROPERTIES
#include "EmptyType.hpp"
using Scroll = add_properties<Type, Naming>;
#else

struct Scroll {
    Name name;
};

#endif
