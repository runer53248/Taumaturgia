#pragma once
#include "Usage/Traits.hpp"

#ifdef NO_PREMADE_PROPERTIES
#include "Usage/User/UserProperties.hpp"
#else
#include "Usage/Premade/PremadeProperties.hpp"
#endif

#ifndef CUSTOM_ORDER_LIST
#include "order_list.hpp"
#include "Taumaturgia/Properties/Structs/Property.hpp"
#else 
#ifdef ORDER_LIST_PATH
#include ORDER_LIST_PATH
#include "Taumaturgia/Properties/Structs/Property.hpp"
#endif
#endif
