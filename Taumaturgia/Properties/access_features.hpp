#pragma once
#include "Taumaturgia/Properties/Helpers/Scheme.hpp"
#include "Taumaturgia/Properties/Helpers/have_get_features.hpp"
#include "Taumaturgia/Traits/trait.hpp"

// MARK: HoldTypes

template <typename T>
struct HoldTypes {
    using types = list<>;
};

// MARK: hold_type

template <typename T, size_t N>
    requires requires {
        typename HoldTypes<std::remove_cvref_t<T>>::types;
    }
using hold_type = boost::mp11::mp_front<
    boost::mp11::mp_drop_c<
        typename HoldTypes<std::remove_cvref_t<T>>::types,
        N>>;

// MARK: getType_index_limit <T>

namespace impl {
template <typename T, size_t S>
struct getType_index_limit_impl {
    static constexpr size_t index = S;
};

template <typename T, size_t S>
    requires have_getType_num_method<T, S>
struct getType_index_limit_impl<T, S> {
    static constexpr size_t index = getType_index_limit_impl<std::remove_cvref_t<T>, S + 1>::index;
};

template <typename T>
struct getType_index_limit_impl<T, 0> {
    static constexpr size_t index = getType_index_limit_impl<std::remove_cvref_t<T>, 1>::index;
};

template <typename T>
    requires(not have_getType_num_method<T, 0>)
struct getType_index_limit_impl<T, 0> {
    static constexpr size_t index = 0;
};
}  // namespace impl

template <typename T>
constexpr size_t getType_index_limit = impl::getType_index_limit_impl<std::remove_cvref_t<T>, 0>::index;

// MARK: base_holds_types <T, size_t>

template <typename T, size_t S>
concept base_holds_types = requires {
    typename hold_type<typename helpers::Scheme_ordered<std::remove_cvref_t<T>>::base,
                       S>;
};

// MARK: have_custom_access <T, size_t>

template <typename T, size_t S>
concept have_custom_access =
    (S >= getType_index_limit<T>) and
    base_holds_types<T, S - getType_index_limit<T>>;

// MARK: getType <size_t>

template <size_t S, typename T>
constexpr decltype(auto) getType(T&& el) noexcept
    requires have_getType_num_method<T, S>
{
    return el.template getType<S>();
}
template <size_t S, typename T>
constexpr decltype(auto) getType(T&& el) noexcept
    requires(not have_getType_num_method<T, S> and
             have_custom_access<T, S>)
{
    using base_type = helpers::Scheme_ordered<std::remove_cvref_t<T>>::base;  // most base type
    constexpr size_t N = S - getType_index_limit<T>;
    using hold_type = hold_type<std::remove_cvref_t<base_type>, N>;

    return trait<hold_type>::get(static_cast<base_type&>(el));
}
template <size_t S, typename T>
constexpr decltype(auto) getType(T&& el) noexcept = delete;

// MARK: getType <TYPE>

template <typename TYPE, size_t S = 0, typename T>
constexpr decltype(auto) getType(T&& el) noexcept
    requires have_getType_type_num_method<T, TYPE, S>
{
    return el.template getType<TYPE, S>();
}
template <typename TYPE, size_t S = 0, typename T>
constexpr decltype(auto) getType(T&& el) noexcept
    requires(not have_getType_type_num_method<T, TYPE, S> and
             trait_accessable<                                                    //
                 typename helpers::Scheme_ordered<std::remove_cvref_t<T>>::base,  //
                 TYPE>)
{
    using base_type = helpers::Scheme_ordered<std::remove_cvref_t<T>>::base;  // most base type
    return trait<TYPE>::get(static_cast<base_type&>(el));
}
template <typename TYPE, size_t S = 0, typename T>
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
    requires(not have_getTypeTaged_method<T, TYPE, TAGS> and
             TAGS::size == 0 and
             trait_accessable<                                                    //
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
