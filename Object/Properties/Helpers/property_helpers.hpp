#pragma once
#include "taged_list.hpp"

#include <boost/mp11.hpp>
using namespace boost::mp11;

template <template <typename> typename property>
struct Property;

template <typename Base, typename L>
struct build_into_impl;

template <typename Base, typename L>
struct build_into_impl {
private:
    using first = mp_first<L>;
    using rest = mp_rest<L>;

public:
    using type = first::template type<typename build_into_impl<Base, rest>::type>;
};

template <typename Base, typename L>
    requires mp_empty<L>::value
struct build_into_impl<Base, L> {
    using type = Base;
};

template <typename Base, typename L>
using build_into_t = build_into_impl<Base, L>::type;

template <typename T>
using value_equal_zero = std::conditional_t<
    (T::value == 0),
    mp_true,
    mp_false>;

template <typename... PROPERTY_LISTS>
using append_and_order_property_lists =
    mp_sort<
        mp_remove_if<
            mp_unique<
                mp_append<
                    PROPERTY_LISTS...>>,
            value_equal_zero>,
        mp_less>;

template <template <typename> typename... properties>
using create_ordered_property_list = append_and_order_property_lists<
    list<Property<properties>...>>;

template <typename T, template <typename> typename... properties>
using add_properties = build_into_t<T, create_ordered_property_list<properties...>>;
