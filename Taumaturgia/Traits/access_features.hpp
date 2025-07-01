#pragma once
#include "Taumaturgia/Properties/Helpers/property_helpers.hpp"
#include "trait.hpp"

// MARK: getType

template <size_t S, typename T>
constexpr decltype(auto) getType(T&& el) noexcept
    requires requires { el.template getType<S>(); }
{
    return el.template getType<S>();
}
template <size_t S, typename T>
constexpr decltype(auto) getType(T&& el) noexcept
    requires(not requires { el.template getType<S>(); } and (S == 0 or requires { el.template getType<S - 1>(); }))
{
    using hold_type = typename std::remove_cvref_t<T>::hold_type;
    using base_type = helpers::Scheme<std::remove_cvref_t<T>>::base;  // most base type

    return trait<hold_type>::get(static_cast<base_type&>(el));
}
template <size_t S, typename T>
constexpr decltype(auto) getType(T&& el) noexcept = delete;

// MARK: getTypeTaged

template <typename TYPE, typename... Tags, typename T>
constexpr decltype(auto) getTypeTaged(T&& el) noexcept
    requires requires { el.template getTypeTaged<TYPE, Tags...>(); }
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
