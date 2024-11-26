#pragma once
#include "Usage/Types/Name/Name.hpp"
#include "Usage/Types/Protection/Protection.hpp"

#ifdef WITH_ADD_PROPERTIES
#include "EmptyType.hpp"
using Helmet = add_properties_ordered<
    Type,
    Naming,
    Protecting>;
#else

struct Helmet {
    Name name;
    Protection protection{};
};

#endif
