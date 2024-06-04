#pragma once
#include "Scheme.hpp"
#include "build_into_t.hpp"

namespace helpers::impl {
template <typename T, template <typename...> typename... properties>
    requires(is_property<properties> and ...)
struct add_properties_impl {
    using type = std::conditional_t<
        have_property<T>,
        build_into_t<
            typename Scheme<T>::base,
            append_and_order_property_lists<
                typename Scheme<T>::list_t,
                create_ordered_property_list<properties...>>>,
        build_into_t<
            T,
            create_ordered_property_list<properties...>>>;
};
}  // namespace helpers::impl

template <typename T, template <typename...> typename... properties>
    requires(is_property<properties> and ...)
using add_properties = helpers::impl::add_properties_impl<T, properties...>::type;
