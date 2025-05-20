#pragma once
#include "taged_list.hpp"

template <typename T, size_t NUM>
concept have_getType_num = requires(T t) {
    { t.template getType<NUM>() };
};

template <typename T, typename TYPE, size_t NUM>
concept have_getType_type_num = requires(T t) {
    { t.template getType<TYPE, NUM>() };
    { t.template getType<TYPE, NUM>() } -> std::same_as<TYPE&>;
};

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
