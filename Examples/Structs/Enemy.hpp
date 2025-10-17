#pragma once
#include "EmptyType.hpp"
#include "Usage/Types/Name/Name.hpp"

using EnemyBuild = add_properties_ordered<
    Type,
    Naming>;

struct EnemyClass {
    property_t<Naming> name;
};

#ifdef WITH_ADD_PROPERTIES
#define USES_ADD_PROPERTIES
using Enemy = EnemyBuild;
#else
using Enemy = EnemyClass;
#endif
