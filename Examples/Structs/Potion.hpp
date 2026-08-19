#pragma once
#include "EmptyType.hpp"
#include "Usage/Types/Name/Name.hpp"

using PotionBuild = add_properties_ordered<
    Type,
    Naming>;

struct PotionClass {
    using hold_type = property_t<Naming>;
    property_t<Naming> name;
};

#ifdef WITH_ADD_PROPERTIES
#define USES_ADD_PROPERTIES
using Potion = PotionBuild;
#else
using Potion = PotionClass;
#endif
