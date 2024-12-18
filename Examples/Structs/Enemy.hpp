#pragma once
#include "Usage/Types/Name/Name.hpp"

#ifdef WITH_ADD_PROPERTIES
#include "EmptyType.hpp"
using Enemy = add_properties_ordered<
    Type,
    Naming>;
#else

struct Enemy {
    Name name;
};

#endif
