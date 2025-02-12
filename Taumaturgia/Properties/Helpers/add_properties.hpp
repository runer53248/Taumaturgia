#pragma once
#include "Taumaturgia/Properties/Structs/Scheme.hpp"
#include "build_into_t.hpp"

namespace helpers::impl {

template <typename property>
struct is_property_type_ordered_impl {};  // invalid template argument
template <template <typename...> typename property>
    requires is_property<property>
struct is_property_type_ordered_impl<Property<property>> {
    static constexpr bool value = true;
};
template <template <typename...> typename property>
    requires is_property<property>
struct is_property_type_ordered_impl<Property_unordered<property>> {
    static constexpr bool value = false;
};

}  // namespace helpers::impl

namespace helpers {

template <typename property>
inline constexpr bool is_property_type_ordered = impl::is_property_type_ordered_impl<property>::value;

template <typename... properties>
inline constexpr bool all_properties_type_ordered = (std::conjunction_v<impl::is_property_type_ordered_impl<properties>...> == true);

template <typename... properties>
inline constexpr bool none_properties_type_ordered = (std::disjunction_v<impl::is_property_type_ordered_impl<properties>...> == false);

}  // namespace helpers

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

template <typename T, typename... properties>
// requires(is_property<properties> and ...)
struct add_properties_impl {
    static_assert(
        all_properties_type_ordered<properties...> or none_properties_type_ordered<properties...>,
        "All properties must be of one type: ordered or unordered.");

    using scheme_type = std::conditional_t<
        all_properties_type_ordered<properties...>,
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
