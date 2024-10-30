#pragma once
#include "Taumaturgia/Properties/Helpers/derived_from_property.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"

namespace impl {

constinit const char a_type_name[] = "Weird";

template <typename T>
class Weird_ : public T {
public:
    using property_data = PropertyData<a_type_name, Weird_, T>;
};

}  // namespace impl

template <typename T>
using Weird = std::conditional_t<
    derived_from_property<T, impl::Weird_>,
    T,
    impl::Weird_<T>>;
