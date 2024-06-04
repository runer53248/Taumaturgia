#pragma once
#include "taged_list.hpp"
#include "create_ordered_property_list.hpp"

namespace helpers {

template <typename T>
struct Scheme;

template <typename T>
    requires(not have_property<T>)
struct Scheme<T> {
    using base = T;
    using list_t = list<>;
};

template <typename T>
    requires(have_property<T>)
struct Scheme<T> {
    using base = Scheme<typename T::property_data::base_type>::base;  // most inner base type
    using list_helper = Scheme<typename T::property_data::base_type>::list_t;
    using list_t = append_and_order_property_lists<  // list of all properties needed to add into base type
        list<typename T::property_data::property_type>,
        list_helper>;
};

}  // namespace helpers
