#pragma once
#include <cstddef>
#include <utility>
#include "taged_list.hpp"

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
    // { t.template getType<TYPE, NUM>() } -> std::same_as<TYPE&>;
    { t.template getType<TYPE, NUM>() } -> not_void;

    { std::as_const(t).template getType<TYPE, NUM>() };
    // { std::as_const(t).template getType<TYPE, NUM>() } -> std::same_as<const TYPE&>;
    { std::as_const(t).template getType<TYPE, NUM>() } -> not_void;
};

template <typename T, typename TYPE, typename... Tags>
concept have_getTypeTaged_method = requires(T t) {
    t.template getTypeTaged<TYPE, Tags...>();
    { t.template getTypeTaged<TYPE, Tags...>() } -> not_void;

    std::as_const(t).template getTypeTaged<TYPE, Tags...>();
    { std::as_const(t).template getTypeTaged<TYPE, Tags...>() } -> not_void;
};

template <typename T, size_t SKIP, typename... Tags>
concept have_getTaged_method = requires(T t) {
    t.template getTaged<SKIP, Tags...>();
    { t.template getTaged<SKIP, Tags...>() } -> not_void;

    std::as_const(t).template getTaged<SKIP, Tags...>();
    { std::as_const(t).template getTaged<SKIP, Tags...>() } -> not_void;
};

template <typename T, typename Signature>
concept have_getTypeOf_method = requires(T t, Signature s) {
    t.getTypeOf(s);
    { t.getTypeOf(s) } -> not_void;

    std::as_const(t).getTypeOf(s);
    { std::as_const(t).getTypeOf(s) } -> not_void;
};

template <typename T, typename CONVERT_TYPE>
concept convertible_to = std::convertible_to<T, CONVERT_TYPE> and not std::same_as<CONVERT_TYPE, void>;

template <typename T, typename TYPE>
concept same_as_result = std::same_as<T, TYPE> or convertible_to<T, TYPE>;

template <typename T, typename TYPE, typename... Tags>
concept have_all_get_features_for_type = requires(std::remove_cvref_t<T> x) {
    { x.getType() } -> same_as_result<TYPE&>;
    { x.template getType<TYPE>() } -> same_as_result<TYPE&>;
    { x.template getType<TYPE, 0>() } -> same_as_result<TYPE&>;
    { x.template getTypeTaged<TYPE, Tags...>() } -> same_as_result<TYPE&>;
    // { x.getTaged() } -> std::same_as<TYPE&>;
    { x.template getTaged<0, Tags...>() } -> same_as_result<TYPE&>;
    { x.getTypeOf(list<TYPE, Tags...>{}) } -> same_as_result<TYPE&>;
    { x.template getTypeOfSignature<list<TYPE, Tags...>>() } -> same_as_result<TYPE&>;

    { std::as_const(x).getType() } -> same_as_result<const TYPE&>;
    { std::as_const(x).template getType<TYPE>() } -> same_as_result<const TYPE&>;
    { std::as_const(x).template getType<TYPE, 0>() } -> same_as_result<const TYPE&>;
    { std::as_const(x).template getTypeTaged<TYPE, Tags...>() } -> same_as_result<const TYPE&>;
    // { std::as_const(x).getTaged() } -> std::same_as<const TYPE&>;
    { std::as_const(x).template getTaged<0, Tags...>() } -> same_as_result<const TYPE&>;
    { std::as_const(x).getTypeOf(list<TYPE, Tags...>{}) } -> same_as_result<const TYPE&>;
    { std::as_const(x).template getTypeOfSignature<list<TYPE, Tags...>>() } -> same_as_result<const TYPE&>;
};
