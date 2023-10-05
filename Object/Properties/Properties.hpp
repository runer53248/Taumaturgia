#pragma once
#include "Damaging.hpp"
#include "Healing.hpp"
#include "Living.hpp"
#include "Naming.hpp"
#include "Protecting.hpp"
#include "Restoring.hpp"
#include "Wearing.hpp"

#include "Helpers/taged_list.hpp"

using order_list = taged_list<
    Living,
    Wearing,
    Damaging,
    Protecting,
    Healing,
    Restoring,
    Naming  // should be last property to add (used closest to type)
    >;      // properties list in order

#include "Helpers/Property.hpp"
