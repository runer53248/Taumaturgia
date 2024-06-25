#pragma once

#ifdef NO_PREMADE_PROPERTIES
#include "Usage/User/UserProperties.hpp"
#else
#include "Usage/Premade/PremadeProperties.hpp"
#endif

#include "Taumaturgia/Properties/Helpers/taged_list.hpp"

using order_list = taged_list<
    Living,
    Wearing,
    Damaging,
    Protecting,
    Healing,
    Restoring,
    Naming  // should be last property to add (used closest to type)
    >;

#include "Taumaturgia/Properties/Structs/Property.hpp"
