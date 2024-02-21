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

// template <typename T>
// using value_equal_zero = mp_bool<T::value == 0>;

template <template <typename> typename T>
concept property_improvement = requires(T<tag>) {
    typename T<tag>::improvement_of;
};

template <typename T>
concept property_improvement_tag = requires(T) {
    typename T::improvement_of;
};

template <typename A, typename B>
struct same_priority {
    // constexpr static bool value =
    //     std::is_same_v<A, B> or
    //     ((A::value == B::value) and A::value != std::numeric_limits<size_t>::max());

    constinit const static auto value = []() -> bool {
        if constexpr (std::is_same_v<A, B>) {
            return true;
        }
        if constexpr (A::value != std::numeric_limits<size_t>::max()) {  // compare two ordered Properties
            return (A::value == B::value);
        }
        // same_priority true if any improved unordered Property improvement_of same as other
        if constexpr (property_improvement_tag<typename A::template type<tag>> and property_improvement_tag<typename B::template type<tag>>) {
            return (std::is_same_v<
                    typename A::template type<tag>::improvement_of,
                    typename B::template type<tag>::improvement_of>);
        }
        if constexpr (property_improvement_tag<typename A::template type<tag>>) {
            return (std::is_same_v<
                    typename A::template type<tag>::improvement_of,
                    typename B::template type<tag>>);
        }
        if constexpr (property_improvement_tag<typename B::template type<tag>>) {
            return (std::is_same_v<
                    typename A::template type<tag>,
                    typename B::template type<tag>::improvement_of>);
        }
        return false;
    }();
};

// template <typename A, typename B>
// struct equivalent_priority {
//     constexpr static bool value =
//         (std::is_same_v<typename A::template type<tag>, typename B::template type<tag>>) or  // same Property or UserProperty (eg. UserProperty_<int, tag>)
//         ((A::value == B::value) and A::value != std::numeric_limits<size_t>::max());       // same priority of known property
// };

template <typename... PROPERTY_LISTS>
using append_and_order_property_lists =
    mp_sort<
        // mp_remove_if< // will remove properties that have 0 value (are not in order_list)
        // mp_unique<
        mp_unique_if<  //
            mp_append<
                PROPERTY_LISTS...>,
            same_priority>,
        // equivalent_priority>,
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
