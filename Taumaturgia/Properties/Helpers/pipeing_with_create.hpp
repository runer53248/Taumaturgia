#pragma once

namespace impl {

template <typename T, typename L>
struct DataAndPropertiesList {
    constexpr DataAndPropertiesList(T&& data) noexcept
        : data{std::forward<T>(data)} {}

    template <typename LL>
    constexpr DataAndPropertiesList(DataAndPropertiesList<T, LL>&& other) noexcept
        : data{std::forward<T>(other.data)} {}

    T data;
};

// create from DataAndPropertiesList
template <typename T, typename... Props>
constexpr decltype(auto) create_from_DAPL(T&& data) {
    using result = add_properties<
        std::remove_cvref_t<T>,
        std::conditional_t<
            trait_accessable<std::remove_cvref_t<T>, typename Props::template apply<tag>::hold_type>,
            Property<UserPropertyAdapter<none>::template type>,  // TODO: autoremove none properties from add_properties list
            Props>...>;

    return (result{std::forward<T>(data)});
    // return (add_properties<std::remove_cvref_t<T>, Props...>{std::forward<T>(data)});
}

}  // namespace impl

// Start DataAndPropertiesList pipe if property is applyable
template <typename T, typename Prop>
    requires requires {
        typename Prop::template apply<std::remove_cvref_t<T>>;
    }
constexpr decltype(auto) operator|(T&& t, Prop) {
    using base_type = std::remove_cvref_t<T>;
    using helper = Prop::template apply<base_type>;
    if constexpr (std::is_same_v<helper, base_type>) {  // ignore unnecessary property for type T
        return (t);
    } else {
        return (impl::DataAndPropertiesList<T, list<Prop>>{std::forward<T>(t)});
    }
}

// Add new property to DataAndPropertiesList
template <typename T, typename... Props, typename Prop2>
constexpr decltype(auto) operator|(impl::DataAndPropertiesList<T, list<Props...>>&& tp, Prop2) {
    using base_type = std::remove_cvref_t<T>;
    using helper = Prop2::template apply<base_type>;
    if constexpr (std::is_same_v<helper, base_type>) {  // ignore unnecesary property for type T
        return (tp);
    } else {
        using namespace boost::mp11;
        using prop_list = helpers::append_and_order_property_lists<list<Props...>, list<Prop2>>;
        if constexpr (mp_contains<list<Props...>, Prop2>::value) {  // skip if property list contain Prop2
            return (tp);
        } else if constexpr (std::same_as<prop_list, list<Props...>>) {  // skip if property list don't change
            return (tp);
        } else {
            using prop_list = helpers::append_and_order_property_lists<list<Props...>, list<Prop2>>;
            return (impl::DataAndPropertiesList<T, prop_list>{std::forward<T>(tp.data)});
        }
    }
}

struct Create_t {
} constexpr Create;

// Create new type object from DataAndPropertiesList
template <typename T, typename... Props>
constexpr decltype(auto) operator|(impl::DataAndPropertiesList<T, list<Props...>>&& tp, Create_t) {
    return impl::create_from_DAPL<T, Props...>(std::forward<T>(tp.data));
}
// Create new type object from DataAndPropertiesList
template <typename T, typename... Props>
constexpr decltype(auto) operator|(impl::DataAndPropertiesList<T, list<Props...>>& tp, Create_t) {
    return impl::create_from_DAPL<T, Props...>(std::forward<T>(tp.data));
}
// skip Create pipe when T isn't DataAndPropertiesList type
template <typename T>
constexpr decltype(auto) operator|(T&& tp, Create_t) {
    return (tp);
}
