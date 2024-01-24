#pragma once

constexpr char b_type_name[] = "B";
template <typename T>
struct B : T {
    using property_data = PropertyData<B, T, b_type_name>;
};
