#pragma once
#include "EmptyType.hpp"
#include "Usage/Types/Health/Health.hpp"

using NpcBuild = add_properties_ordered<
    Type,
    Living>;

struct NpcClass {
    Health hp{5};
};

#ifdef WITH_ADD_PROPERTIES
#define USES_ADD_PROPERTIES
using Npc = NpcBuild;
#else
using Npc = NpcClass;
#endif
