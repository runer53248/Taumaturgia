#pragma once
#include "Usage/Types/Health/Health.hpp"

#ifdef WITH_ADD_PROPERTIES
#include "EmptyType.hpp"
using Npc = add_properties<
    Type,
    Living>;
#else

struct Npc {       // don't have name
    Health hp{5};  // TODO: default values
};

#endif
