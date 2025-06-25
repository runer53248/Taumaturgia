#pragma once
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"

template <typename T>
class B : public T {
public:
    using property_data = PropertyData<B, T>;
    using hold_type = void;
};
