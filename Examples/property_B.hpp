#pragma once
#include "Object/Properties/Helpers/PropertyData.hpp"

constexpr char b_type_name[] = "B";
template <typename T>
struct B : T {
    using property_data = PropertyData<b_type_name, B, T>;
};
