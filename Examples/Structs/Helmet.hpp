#pragma once
#include "Taumaturgia/Types/Name.hpp"
#include "Taumaturgia/Types/Protection.hpp"

#ifdef WITH_ADD_PROPERTIES
#include "EmptyType.hpp"
using Helmet = add_properties<Type, Naming, Protecting>;
#else

struct Helmet {
    Name name;
    Protection protection{};
};

#endif
