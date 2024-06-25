#pragma once
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"

constinit const char b_type_name[] = "B";
template <typename T>
class B : public T {
public:
    using property_data = PropertyData<b_type_name, B, T>;
};
