#pragma once
#include "Examples/is_derived_from_template_base.hpp"
#include "Object/Properties/Helpers/PropertyData.hpp"

namespace impl {

constexpr char a_type_name[] = "A";

template <typename T>
struct A_ : T {
    using property_data = PropertyData<a_type_name, A_, T>;
};

}  // namespace impl

template <typename T>
using A = std::conditional_t<
    is_derived_from_template_base<T, impl::A_>::value,
    T,
    impl::A_<T>>;
