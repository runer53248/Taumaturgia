#pragma once
#include "Object/Properties/PropertyData.hpp"

namespace impl {

constexpr char a_type_name[] = "A";

template <typename T>
struct A_ : T {
    using property_data = PropertyData<a_type_name, A_, T>;
};

}  // namespace impl

template <typename T>
using A = std::conditional_t<
    is_base_of_template<impl::A_, T>::value,
    T,
    impl::A_<T>>;
