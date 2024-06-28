#pragma once
#include "properties_info.hpp"

using list_of_types = list<
    properties_type<Properties::Health>,
    properties_type<Properties::CureHealth>,
    properties_type<Properties::Damage>,
    properties_type<Properties::Protection>,
    properties_type<Properties::Restore>,
    properties_type<Properties::Wear>>;
