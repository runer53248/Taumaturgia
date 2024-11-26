#pragma once
#include <boost/mp11.hpp>
#include "same_priority.hpp"

template <template <typename...> typename property>
    requires is_property<property>
struct Property;

template <template <typename...> typename property>
    requires is_property<property>
struct Property_unordered;

namespace helpers {

template <typename... PROPERTY_LISTS>
using append_and_order_property_lists =
    boost::mp11::mp_sort<
        boost::mp11::mp_unique_if<  //
            boost::mp11::mp_append<
                PROPERTY_LISTS...>,
            impl::same_priority>,
        boost::mp11::mp_less>;

template <template <template <typename...> typename> typename Property_type,
          template <typename...> typename... properties>
    requires(is_property<properties> and ...)
using create_property_list_of_type = append_and_order_property_lists<
    list<Property_type<properties>...>>;  // for both ordered and unordered

template <template <typename...> typename... properties>
    requires(is_property<properties> and ...)
using create_ordered_property_list = create_property_list_of_type<Property, properties...>;

template <template <typename...> typename... properties>
    requires(is_property<properties> and ...)
using create_unordered_property_list = create_property_list_of_type<Property_unordered, properties...>;

template <typename... properties>
// requires(is_property<properties> and ...)
using create_property_list = append_and_order_property_lists<
    list<properties...>>;

}  // namespace helpers
