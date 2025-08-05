#pragma once
#include "Taumaturgia/Properties/Helpers/have_get_features.hpp"
#include "Taumaturgia/Properties/Helpers/property_helpers.hpp"
#include "trait.hpp"

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
        requires { typename helpers::Scheme<std::remove_cvref_t<T>>::base::hold_type; }  //
        and not have_getType_num_method<T, S>                                            //
        and (S == 0 or have_getType_num_method<T, S - 1>))
{
    using base_type = helpers::Scheme<std::remove_cvref_t<T>>::base;  // most base type
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
             sizeof...(Tags) == 0 and trait_accessable<                                            //
                                          typename helpers::Scheme<std::remove_cvref_t<T>>::base,  //
                                          TYPE>)
{
    using base_type = helpers::Scheme<std::remove_cvref_t<T>>::base;  // most base type
    return trait<TYPE>::get(static_cast<base_type&>(el));
}
template <typename TYPE, typename... Tags, typename T>
constexpr decltype(auto) getTypeTaged(T&& el) noexcept = delete;
