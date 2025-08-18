#pragma once
#include "EmptyType.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "Usage/Types/Protection/Protection.hpp"

using HelmetBuild = add_properties_ordered<
    Type,
    Naming,
    Protecting>;

struct HelmetClass {
    Name name;
    Protection protection{};
};

#ifdef WITH_ADD_PROPERTIES
#define USES_ADD_PROPERTIES
using Helmet = HelmetBuild;
#else
using Helmet = HelmetClass;
#endif
