#pragma once
#include "Taumaturgia/Properties/Helpers/derived_from_property.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"

namespace impl {

constinit const char a_type_name[] = "A";

template <typename T>
class A_ : public T {
public:
    using property_data = PropertyData<a_type_name, A_, T>;
};

}  // namespace impl

template <typename T>
using A = std::conditional_t<
    derived_from_property<T, impl::A_>,
    T,
    impl::A_<T>>;
