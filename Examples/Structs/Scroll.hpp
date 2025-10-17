#pragma once
#include "EmptyType.hpp"
#include "Usage/Types/Name/Name.hpp"
using ScrollBuild = add_properties_ordered<
    Type,
    Naming>;

struct ScrollClass {
    property_t<Naming> name;
};

#ifdef WITH_ADD_PROPERTIES
#define USES_ADD_PROPERTIES
using Scroll = ScrollBuild;
#else
using Scroll = ScrollClass;
#endif
