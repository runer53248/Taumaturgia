#pragma once
#include <cstddef>
#include <utility>
// #include "taged_list.hpp"

template <typename... T>
struct list;

template <typename T>
concept not_void = not std::same_as<T, void>;

template <typename T, typename TYPE>
concept have_getType_type_method = requires(T t) {
    { t.template getType<TYPE>() };
    { t.template getType<TYPE>() } -> not_void;

    { std::as_const(t).template getType<TYPE>() };
    { std::as_const(t).template getType<TYPE>() } -> not_void;
};

template <typename T, size_t NUM>
concept have_getType_num_method = requires(T t) {
    { t.template getType<NUM>() };
    { t.template getType<NUM>() } -> not_void;

    { std::as_const(t).template getType<NUM>() };
    { std::as_const(t).template getType<NUM>() } -> not_void;
};

template <typename T, typename TYPE, size_t NUM>
concept have_getType_type_num_method = requires(T t) {
    { t.template getType<TYPE, NUM>() };
    { t.template getType<TYPE, NUM>() } -> std::same_as<TYPE&>;

    { std::as_const(t).template getType<TYPE, NUM>() };
    { std::as_const(t).template getType<TYPE, NUM>() } -> std::same_as<const TYPE&>;
};

template <typename T, typename TYPE, typename TAGS = no_tag>
concept have_getTypeTaged_method = requires(T t) {
    t.template getTypeTaged<TYPE, TAGS>();
    { t.template getTypeTaged<TYPE, TAGS>() } -> not_void;

    std::as_const(t).template getTypeTaged<TYPE, TAGS>();
    { std::as_const(t).template getTypeTaged<TYPE, TAGS>() } -> not_void;
};

template <typename T, size_t SKIP, typename TAGS = no_tag>
concept have_getTaged_method = requires(T t) {
    t.template getTaged<SKIP, TAGS>();
    { t.template getTaged<SKIP, TAGS>() } -> not_void;

    std::as_const(t).template getTaged<SKIP, TAGS>();
    { std::as_const(t).template getTaged<SKIP, TAGS>() } -> not_void;
};

template <typename T, typename Signature>
concept have_getTypeOf_method = requires(T t, Signature s) {
    t.getTypeOf(s);
    { t.getTypeOf(s) } -> not_void;

    std::as_const(t).getTypeOf(s);
    { std::as_const(t).getTypeOf(s) } -> not_void;
};

template <typename T, typename TYPE>
concept have_all_get_features_for_type = requires(std::remove_cvref_t<T> x) {
    { x.getType() } -> std::same_as<TYPE&>;
    { x.template getType<TYPE>() } -> std::same_as<TYPE&>;
    { x.template getType<TYPE, 0>() } -> std::same_as<TYPE&>;
    { x.template getTypeTaged<TYPE>() } -> std::same_as<TYPE&>;
    { x.getTaged() } -> std::same_as<TYPE&>;
    { x.template getTaged<0>() } -> std::same_as<TYPE&>;
    { x.getTypeOf(list<TYPE, Tags<>>{}) } -> std::same_as<TYPE&>;
    { x.template getTypeOfSignature<list<TYPE, Tags<>>>() } -> std::same_as<TYPE&>;
    
    { std::as_const(x).getType() } -> std::same_as<const TYPE&>;
    { std::as_const(x).template getType<TYPE>() } -> std::same_as<const TYPE&>;
    { std::as_const(x).template getType<TYPE, 0>() } -> std::same_as<const TYPE&>;
    { std::as_const(x).template getTypeTaged<TYPE>() } -> std::same_as<const TYPE&>;
    { std::as_const(x).getTaged() } -> std::same_as<const TYPE&>;
    { std::as_const(x).template getTaged<0>() } -> std::same_as<const TYPE&>;
    { std::as_const(x).getTypeOf(list<TYPE, Tags<>>{}) } -> std::same_as<const TYPE&>;
    { std::as_const(x).template getTypeOfSignature<list<TYPE, Tags<>>>() } -> std::same_as<const TYPE&>;
};
