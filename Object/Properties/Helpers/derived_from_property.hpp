#pragma once
#include <type_traits>
#include "taged_list.hpp"

template <typename derived, template <typename> typename property>
struct is_derived_from_property_impl {
    template <typename T>
    static constexpr std::true_type test(const property<T>*);        // for properties (ie. impl::Wearing_<T>)
    static constexpr std::true_type test(const property<derived>*);  // for conditional properties aliases (ie. Wearing<T>)
    static constexpr std::false_type test(...);
    using type = decltype(test(std::declval<const derived*>()));
};

template <typename derived, template <typename> typename property>
using is_derived_from_property = typename is_derived_from_property_impl<derived, property>::type;

template <typename T, template <typename> typename property>
concept derived_from_property = is_derived_from_property<T, property>::value;
