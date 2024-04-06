#pragma once
#include "Taumaturgia/Properties/Helpers/PropertyData.hpp"

constinit char b_type_name[] = "B";
template <typename T>
struct B : T {
    using property_data = PropertyData<b_type_name, B, T>;
};
