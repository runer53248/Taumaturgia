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

template <typename TYPE, isTag TAGS = no_tag, typename T>
constexpr decltype(auto) getTypeTaged(T&& el) noexcept
    requires have_getTypeTaged_method<T, TYPE, TAGS>
{
    return el.template getTypeTaged<TYPE, TAGS>();
}
template <typename TYPE, isTag TAGS = no_tag, typename T>
constexpr decltype(auto) getTypeTaged(T&& el) noexcept
    requires(not requires { el.template getTypeTaged<TYPE, TAGS>(); } and
             TAGS::size == 0 and trait_accessable<                                                    //
                                          typename helpers::Scheme_ordered<std::remove_cvref_t<T>>::base,  //
                                          TYPE>)
{
    using base_type = helpers::Scheme_ordered<std::remove_cvref_t<T>>::base;  // most base type
    return trait<TYPE>::get(static_cast<base_type&>(el));
}
template <typename TYPE, isTag TAGS = no_tag, typename T>
constexpr decltype(auto) getTypeTaged(T&& el) noexcept = delete;

template <typename T, typename Type, typename TAGS = no_tag>
concept is_getTypeTaged_valid = requires {
    getTypeTaged<Type, TAGS>(std::declval<T&>());
};

// MARK: getTaged

template <isTag TAGS = no_tag, typename T>
constexpr decltype(auto) getTaged(T&& el) noexcept
    requires have_getTaged_method<T, 0, TAGS>
{
    return el.template getTaged<TAGS>();
}
template <isTag TAGS = no_tag, typename T>
constexpr decltype(auto) getTaged(T&& el) noexcept = delete;

template <size_t SKIP, isTag TAGS = no_tag, typename T>
constexpr decltype(auto) getTaged(T&& el) noexcept
    requires have_getTaged_method<T, SKIP, TAGS>
{
    return el.template getTaged<SKIP, TAGS>();
}
template <size_t SKIP, isTag TAGS = no_tag, typename T>
constexpr decltype(auto) getTaged(T&& el) noexcept = delete;

template <typename T, typename TAGS>
concept is_getTaged_valid = requires {
    getTaged<TAGS>(std::declval<T&>());
    getTaged<0, TAGS>(std::declval<T&>());
};
