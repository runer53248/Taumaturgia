#pragma once
#include "Taumaturgia/Properties/Structs/Scheme.hpp"
#include "build_into_t.hpp"

namespace helpers::impl {
template <typename T, template <typename...> typename... properties>
    requires(is_property<properties> and ...)
struct add_properties_ordered_impl {
    using type = std::conditional_t<
        have_property_data<T>,
        build_into_t<
            typename Scheme<T>::base,
            append_and_order_property_lists<
                typename Scheme<T>::list_t,
                create_ordered_property_list<properties...>>>,
        build_into_t<
            T,
            create_ordered_property_list<properties...>>>;
};

template <typename T, template <typename...> typename... properties>
    requires(is_property<properties> and ...)
struct add_properties_unordered_impl {
    using type = std::conditional_t<
        have_property_data<T>,
        build_into_t<
            typename Scheme_unordered<T>::base,
            append_and_order_property_lists<
                typename Scheme_unordered<T>::list_t,
                create_unordered_property_list<properties...>>>,
        build_into_t<
            T,
            create_unordered_property_list<properties...>>>;
};

template <typename property>
struct property_type_ordered {};
template <template <typename...> typename property>
    requires is_property<property>
struct property_type_ordered<Property<property>> {
    static constexpr bool value = true;
};
template <template <typename...> typename property>
    requires is_property<property>
struct property_type_ordered<Property_unordered<property>> {
    static constexpr bool value = false;
};

template <typename T, typename... properties>
// requires(is_property<properties> and ...)
struct add_properties_impl {
    static constexpr auto num_of_ordered =  // count properties from Property
        boost::mp11::mp_count<
            list<boost::mp11::mp_bool<property_type_ordered<properties>::value>...>,
            boost::mp11::mp_true>::value;
    static_assert(num_of_ordered == 0 or num_of_ordered == sizeof...(properties), "All properties must be from one type: Property or Property_unordered.");

    static constexpr bool is_ordered = num_of_ordered;

    using scheme_type = std::conditional_t<
        is_ordered,
        Scheme<T>,
        Scheme_unordered<T>>;

    using type = std::conditional_t<
        have_property_data<T>,
        build_into_t<
            typename scheme_type::base,
            append_and_order_property_lists<
                typename scheme_type::list_t,
                create_property_list<properties...>>>,
        build_into_t<
            T,
            create_property_list<properties...>>>;
};

}  // namespace helpers::impl

template <typename T, template <typename...> typename... properties>
    requires(is_property<properties> and ...)
using add_properties_ordered = helpers::impl::add_properties_ordered_impl<T, properties...>::type;

template <typename T, template <typename...> typename... properties>
    requires(is_property<properties> and ...)
using add_properties_unordered = helpers::impl::add_properties_unordered_impl<T, properties...>::type;

template <typename T, typename... properties>
// requires(is_property<properties> and ...)
using add_properties = helpers::impl::add_properties_impl<T, properties...>::type;
