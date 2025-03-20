#pragma once
#include <utility>

template <typename...>
struct list;

template <typename T, typename type>
concept have_get_features = requires(std::remove_cvref_t<T> x) {
    { x.getType() } -> std::same_as<type&>;
    { std::as_const(x).getType() } -> std::same_as<const type&>;

    { x.template getType<type>() } -> std::same_as<type&>;
    { std::as_const(x).template getType<type>() } -> std::same_as<const type&>;

    { x.template getTypeTaged<type>() } -> std::same_as<type&>;
    { std::as_const(x).template getTypeTaged<type>() } -> std::same_as<const type&>;

    { x.template getTypeTaged<type>() } -> std::same_as<type&>;
    { std::as_const(x).template getTypeTaged<type>() } -> std::same_as<const type&>;

    { x.getTaged() } -> std::same_as<type&>;
    { std::as_const(x).getTaged() } -> std::same_as<const type&>;

    { x.template getTaged<0>() } -> std::same_as<type&>;
    { std::as_const(x).template getTaged<0>() } -> std::same_as<const type&>;

    { x.getTypeOf(list<type>{}) } -> std::same_as<type&>;
    { std::as_const(x).getTypeOf(list<type>{}) } -> std::same_as<const type&>;

    { x.template getTypeOfSignature<list<type>>() } -> std::same_as<type&>;
    { std::as_const(x).template getTypeOfSignature<list<type>>() } -> std::same_as<const type&>;
};
