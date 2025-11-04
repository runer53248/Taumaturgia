#pragma once
#include "Taumaturgia/Properties/Helpers/Scheme.hpp"
#include "Taumaturgia/Properties/Helpers/have_get_features.hpp"
#include "Taumaturgia/Traits/trait.hpp"

// MARK: getType

template <size_t S, typename T>
constexpr decltype(auto) getType(T&& el) noexcept
    requires have_getType_num_method<T, S>
{
    return el.template getType<S>();
}
template <size_t S, typename T>
constexpr decltype(auto) getType(T&& el) noexcept
    requires(
        requires { typename helpers::Scheme_ordered<std::remove_cvref_t<T>>::base::hold_type; }  //
        and not have_getType_num_method<T, S>                                                    //
        and (S == 0 or have_getType_num_method<T, S - 1>))
{
    using base_type = helpers::Scheme_ordered<std::remove_cvref_t<T>>::base;  // most base type
    using hold_type = typename std::remove_cvref_t<base_type>::hold_type;

    return trait<hold_type>::get(static_cast<base_type&>(el));
}
template <size_t S, typename T>
constexpr decltype(auto) getType(T&& el) noexcept = delete;

// MARK: getTypeTaged

template <typename TYPE, typename... Tags, typename T>
constexpr decltype(auto) getTypeTaged(T&& el) noexcept
    requires have_getTypeTaged_method<T, TYPE, Tags...>
{
    return el.template getTypeTaged<TYPE, Tags...>();
}
template <typename TYPE, typename... Tags, typename T>
constexpr decltype(auto) getTypeTaged(T&& el) noexcept
    requires(not requires { el.template getTypeTaged<TYPE, Tags...>(); } and
             sizeof...(Tags) == 0 and trait_accessable<                                                    //
                                          typename helpers::Scheme_ordered<std::remove_cvref_t<T>>::base,  //
                                          TYPE>)
{
    using base_type = helpers::Scheme_ordered<std::remove_cvref_t<T>>::base;  // most base type
    return trait<TYPE>::get(static_cast<base_type&>(el));
}
template <typename TYPE, typename... Tags, typename T>
constexpr decltype(auto) getTypeTaged(T&& el) noexcept = delete;

template <typename T, typename Type, typename... Tags>
concept is_getTypeTaged_valid = requires {
    getTypeTaged<Type, Tags...>(std::declval<T&>());
};

// MARK: getTaged

template <typename... Tags, typename T>
constexpr decltype(auto) getTaged(T&& el) noexcept
    requires have_getTaged_method<T, 0, Tags...>
{
    return el.template getTaged<Tags...>();
}
template <typename... Tags, typename T>
constexpr decltype(auto) getTaged(T&& el) noexcept = delete;

template <size_t SKIP, typename... Tags, typename T>
constexpr decltype(auto) getTaged(T&& el) noexcept
    requires have_getTaged_method<T, SKIP, Tags...>
{
    return el.template getTaged<SKIP, Tags...>();
}
template <size_t SKIP, typename... Tags, typename T>
constexpr decltype(auto) getTaged(T&& el) noexcept = delete;

template <typename T, typename... Tags>
concept is_getTaged_valid = requires {
    getTaged<Tags...>(std::declval<T&>());
    getTaged<0, Tags...>(std::declval<T&>());
};
