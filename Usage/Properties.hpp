#pragma once
#include "Usage/User/UserProperties.hpp"

#ifndef CUSTOM_ORDER_LIST
#include "order_list.hpp"
#else
#ifdef ORDER_LIST_PATH
#include ORDER_LIST_PATH
#else
static_assert(false, "ORDER_LIST_PATH undefined");
#endif
#endif
#include "Taumaturgia/Properties/Structs/Property.hpp"
