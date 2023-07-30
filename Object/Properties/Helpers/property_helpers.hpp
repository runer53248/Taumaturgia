#pragma once
#include <boost/mp11.hpp>
#include "taged_list.hpp"
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
        // mp_remove_if< // will remove properties that have 0 value (are not in order_list)
        mp_unique<
            mp_append<
                PROPERTY_LISTS...>>,
        // value_equal_zero>,
        mp_less>;

template <template <typename> typename... properties>
using create_ordered_property_list = append_and_order_property_lists<
    list<Property<properties>...>>;

template <typename T>
concept is_property_type = requires {
    typename T::property_data;
    typename T::property_data::base_type;
    typename T::property_data::property_type;
};

template <typename T, bool F = is_property_type<T>>
struct Scheme;

template <typename T>
struct Scheme<T, false> {
    using base = T;
    using list = list<>;
};

template <typename T>
struct Scheme<T, true> {
    using base = Scheme<typename T::property_data::base_type>::base;  // most inner base type
    using list_helper = Scheme<typename T::property_data::base_type>::list;
    using list = append_and_order_property_lists<  // list of all properties needed to add into base type
        list<typename T::property_data::property_type>,
        list_helper>;
};

template <typename T, template <typename> typename... properties>
struct add_properties_impl {
    using type = std::conditional_t<
        is_property_type<T>,
        build_into_t<
            typename Scheme<T>::base,
            append_and_order_property_lists<
                typename Scheme<T>::list,
                create_ordered_property_list<properties...>>>,
        build_into_t<
            T,
            create_ordered_property_list<properties...>>>;
};

template <typename T, template <typename> typename... properties>
using add_properties = add_properties_impl<T, properties...>::type;
