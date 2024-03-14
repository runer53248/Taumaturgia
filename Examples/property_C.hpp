#pragma once
#include <type_traits>
#include "Object/Properties/Helpers/PropertyData.hpp"

namespace impl {

constexpr char c_type_name[] = "C";

template <typename T>
struct C_ : T {
    using property_data = PropertyData<a_type_name, C_, T>;
};

}  // namespace impl

template <typename T, template <typename> typename property>
concept propertyable = requires(T x) {
    std::is_nothrow_convertible_v<T, property<T>>;
};

template <typename T>
using C = std::conditional_t<
    propertyable<T, impl::C_>,
    T,
    impl::C_<T>>;
