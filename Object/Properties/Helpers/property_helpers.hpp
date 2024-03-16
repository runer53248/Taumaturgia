#pragma once
#include "PropertyData.hpp"

#include <boost/mp11.hpp>
using namespace boost::mp11;

namespace helpers {

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

template <template <typename...> typename property>
concept is_property_improvement = is_property<property> and requires {
    typename property<tag>::improvement_of;
};

template <typename A, typename B>
struct is_same_priority {
    template <typename T>
    using improvement_type_of = typename T::template type<tag>::improvement_of;

    template <typename T>
    using type_of = typename T::template type<tag>;

    constinit const static auto value = []() -> bool {
        if constexpr (std::is_same_v<A, B>) {
            return true;
        }
        if constexpr (A::value != std::numeric_limits<size_t>::max()) {  // compare two ordered Properties
            return (A::value == B::value);
        }
        // same_priority true if any improved unordered Property improvement_of same as other
        if constexpr (is_property_improvement<A::template type> and is_property_improvement<B::template type>) {
            return (std::is_same_v<
                    improvement_type_of<A>,
                    improvement_type_of<B>>);
        }
        if constexpr (is_property_improvement<A::template type>) {
            return (std::is_same_v<
                    improvement_type_of<A>,
                    type_of<B>>);
        }
        if constexpr (is_property_improvement<B::template type>) {
            return (std::is_same_v<
                    type_of<A>,
                    improvement_type_of<B>>);
        }
        return false;
    }();
};

template <typename A, typename B>
concept same_priority = is_same_priority<A, B>::value;

template <typename... PROPERTY_LISTS>
using append_and_order_property_lists =
    mp_sort<
        mp_unique_if<  //
            mp_append<
                PROPERTY_LISTS...>,
            is_same_priority>,
        mp_less>;

template <template <typename...> typename... properties>
    requires(is_property<properties> and ...)
using create_ordered_property_list = append_and_order_property_lists<
    list<Property<properties>...>>;

template <typename T>
concept is_type_with_added_properties = requires {
    typename T::property_data;
};

template <typename T>
struct Scheme;

template <typename T>
    requires(not is_type_with_added_properties<T>)
struct Scheme<T> {
    using base = T;
    using list = list<>;
};

template <typename T>
    requires(is_type_with_added_properties<T>)
struct Scheme<T> {
    using base = Scheme<typename T::property_data::base_type>::base;  // most inner base type
    using list_helper = Scheme<typename T::property_data::base_type>::list;
    using list = append_and_order_property_lists<  // list of all properties needed to add into base type
        list<typename T::property_data::property_type>,
        list_helper>;
};

template <typename T, template <typename...> typename... properties>
    requires(is_property<properties> and ...)
struct add_properties_impl {
    using type = std::conditional_t<
        is_type_with_added_properties<T>,
        build_into_t<
            typename Scheme<T>::base,
            append_and_order_property_lists<
                typename Scheme<T>::list,
                create_ordered_property_list<properties...>>>,
        build_into_t<
            T,
            create_ordered_property_list<properties...>>>;
};

}  // namespace helpers

template <typename T, template <typename...> typename... properties>
    requires(is_property<properties> and ...)
using add_properties = helpers::add_properties_impl<T, properties...>::type;

template <template <typename...> typename... properties>
    requires(is_property<properties> and ...)
struct properties_list {
    template <typename T>
    using add_properties = ::add_properties<T, properties...>;
};
