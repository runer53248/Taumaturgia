#pragma once
#include <type_traits>
#include "Object/Properties/Helpers/PropertyData.hpp"
#include "Object/Properties/Helpers/propertyable.hpp"

namespace impl {

constexpr char c_type_name[] = "C";

template <typename T>
struct C_ : T {
    using property_data = PropertyData<a_type_name, C_, T>;
};

}  // namespace impl

template <typename T>
using C = std::conditional_t<
    propertyable<T, impl::C_>,
    T,
    impl::C_<T>>;
