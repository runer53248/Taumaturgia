#pragma once

#ifdef NO_PREMADE_PROPERTIES
#include "Taumaturgia/User/UserProperties.hpp"
#else
#include "Premade/PremadeProperties.hpp"
#endif

#include "Helpers/taged_list.hpp"

using order_list = taged_list<
    Living,
    Wearing,
    Damaging,
    Protecting,
    Healing,
    Restoring,
    Naming  // should be last property to add (used closest to type)
    >;

#include "Helpers/Property.hpp"
