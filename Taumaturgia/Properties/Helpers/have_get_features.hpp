#pragma once
#include "taged_list.hpp"

template <typename T>
concept not_void = not std::same_as<T, void>;

template <typename T, size_t NUM>
concept have_getType_num = requires(T t) {
    { t.template getType<NUM>() };
    { t.template getType<NUM>() } -> not_void;
};

template <typename T, typename TYPE, size_t NUM>
concept have_getType_type_num = requires(T t) {
    { t.template getType<TYPE, NUM>() };
    { t.template getType<TYPE, NUM>() } -> std::same_as<TYPE&>;
};

template <typename T, typename TYPE, typename... Tags>
concept get_type_taged_able = requires(T t) {
    t.template getTypeTaged<TYPE, Tags...>();
    { t.template getTypeTaged<TYPE, Tags...>() } -> not_void;
};

template <typename T, size_t SKIP, typename... Tags>
concept get_taged_able = requires(T t) {
    t.template getTaged<SKIP, Tags...>();
    { t.template getTaged<SKIP, Tags...>() } -> not_void;
};

template <typename T, typename Signature>
concept get_type_of_able = requires(T t, Signature s) {
    t.getTypeOf(s);
    { t.getTypeOf(s) } -> not_void;
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
