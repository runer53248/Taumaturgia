#pragma once
#include "properties_to_type.hpp"

using list_of_types = list<
    properties_to_type<Properties::Health>,
    properties_to_type<Properties::CureHealth>,
    properties_to_type<Properties::Damage>,
    properties_to_type<Properties::Protection>,
    properties_to_type<Properties::Restore>,
    properties_to_type<Properties::Wear>>;
