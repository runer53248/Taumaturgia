#pragma once
#include "Taumaturgia/Properties/Helpers/Scheme.hpp"
#include "Taumaturgia/Properties/Helpers/have_get_features.hpp"
#include "Taumaturgia/Traits/trait.hpp"

// MARK:

template <typename T>
struct HoldTypes {
    using types = list<>;
};

template <typename T, size_t N>
    requires requires {
        typename HoldTypes<std::remove_cvref_t<T>>::types;
    }
using hold_type = boost::mp11::mp_front<
    boost::mp11::mp_drop_c<
        typename HoldTypes<std::remove_cvref_t<T>>::types,
        N>>;

// MARK: max_getType<T>

template <typename T, size_t S>
struct max_getType_num {
    static constexpr size_t index = S;
};

template <typename T, size_t S>
    requires have_getType_num_method<T, S>
struct max_getType_num<T, S> {
    static constexpr size_t index = max_getType_num<std::remove_cvref_t<T>, S + 1>::index;
};

template <typename T>
struct max_getType_num<T, 0> {
    static constexpr size_t index = max_getType_num<std::remove_cvref_t<T>, 1>::index;
};

template <typename T>
    requires(not have_getType_num_method<T, 0>)
struct max_getType_num<T, 0> {
    static constexpr size_t index = 0;
};

template <typename T>
constexpr size_t max_getType = max_getType_num<std::remove_cvref_t<T>, 0>::index;

// MARK: getType<size_t>

template <size_t S, typename T>
constexpr decltype(auto) getType(T&& el) noexcept
    requires have_getType_num_method<T, S>
{
    return el.template getType<S>();
}
template <size_t S, typename T>
constexpr decltype(auto) getType(T&& el) noexcept
    requires(not have_getType_num_method<T, S> and
             (S == 0) and
             requires {
                 //  typename helpers::Scheme_ordered<std::remove_cvref_t<T>>::base::template hold_types<0>;
                 typename hold_type<typename helpers::Scheme_ordered<std::remove_cvref_t<T>>::base, 0>;
             })
{
    using base_type = helpers::Scheme_ordered<std::remove_cvref_t<T>>::base;  // most base type
    // using hold_type = typename std::remove_cvref_t<base_type>::template hold_types<0>;
    using hold_type = hold_type<std::remove_cvref_t<base_type>, 0>;

    return trait<hold_type>::get(static_cast<base_type&>(el));
}
template <size_t S, typename T>
constexpr decltype(auto) getType(T&& el) noexcept
    requires((S >= max_getType<T> and S > 0) and
             requires {
                 //   typename helpers::Scheme_ordered<std::remove_cvref_t<T>>::base::template hold_types<S - max_getType<T>>;
                 typename hold_type<typename helpers::Scheme_ordered<std::remove_cvref_t<T>>::base, S - max_getType<T>>;
             })
{
    using base_type = helpers::Scheme_ordered<std::remove_cvref_t<T>>::base;  // most base type
    constexpr size_t N = S - max_getType<T>;
    // using hold_type = typename std::remove_cvref_t<base_type>::template hold_types<N>;
    using hold_type = hold_type<std::remove_cvref_t<base_type>, N>;

    return trait<hold_type>::get(static_cast<base_type&>(el));
}
template <size_t S, typename T>
constexpr decltype(auto) getType(T&& el) noexcept = delete;

// MARK: getType<TYPE>

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
