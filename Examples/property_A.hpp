#pragma once
#include "Taumaturgia/Properties/Helpers/derived_from_property.hpp"
#include "Taumaturgia/Properties/Helpers/PropertyData.hpp"

namespace impl {

constinit char a_type_name[] = "A";

template <typename T>
struct A_ : T {
    using property_data = PropertyData<a_type_name, A_, T>;
};

}  // namespace impl

template <typename T>
using A = std::conditional_t<
    derived_from_property<T, impl::A_>,
    T,
    impl::A_<T>>;
