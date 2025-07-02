#pragma once
#include <cstddef>  // for std::size_t
#include <type_traits>
#include <utility>  // for as_const
#include "CustomAccessType.hpp"

namespace traits::helpers {

template <typename T, typename CONVERT_TYPE>
concept convertible_to = std::convertible_to<T, CONVERT_TYPE> and not std::same_as<CONVERT_TYPE, void>;

template <typename T, typename TYPE, typename CONVERT_TYPE>
concept same_as_or_convertible_to = std::same_as<T, TYPE> or convertible_to<T, CONVERT_TYPE>;

template <typename T, typename TRAIT, typename TYPE, typename CONVERT_TYPE = void>
concept accessable = requires(std::remove_cvref_t<T> x) {
    { TRAIT::get(x) } -> same_as_or_convertible_to<TYPE&, CONVERT_TYPE>;
    { TRAIT::get(std::as_const(x)) } -> same_as_or_convertible_to<const TYPE&, const CONVERT_TYPE>;
};

template <typename T, typename TYPE, typename CONVERT_TYPE>
concept custom_type_accessable = requires(std::remove_cvref_t<T> x) {
    { ::traits::CustomAccessType<TYPE, std::remove_cvref_t<T>>::get(x) } -> same_as_or_convertible_to<TYPE&, CONVERT_TYPE>;
    { ::traits::CustomAccessType<TYPE, std::remove_cvref_t<T>>::get(std::as_const(x)) } -> same_as_or_convertible_to<const TYPE&, const CONVERT_TYPE>;
};

template <typename T, typename TYPE>
concept type_accessable = requires(std::remove_cvref_t<T> x) {
    { x.type } -> std::same_as<TYPE&>;
    { std::as_const(x).type } -> std::same_as<const TYPE&>;
};

template <typename T, typename TYPE>
concept get_type_accessable = requires(std::remove_cvref_t<T> x) {
    { x.getType() } -> std::same_as<TYPE&>;
    { std::as_const(x).getType() } -> std::same_as<const TYPE&>;
};

template <typename T, typename TYPE>
concept get_type_taged_accessable = requires(std::remove_cvref_t<T> x) {
    { x.template getTypeTaged<TYPE>() } -> std::same_as<TYPE&>;
    { std::as_const(x).template getTypeTaged<TYPE>() } -> std::same_as<const TYPE&>;
};

template <typename T, typename TYPE, typename CONVERT_TYPE, size_t DIG = 0>
concept get_type_template_accessable = requires(std::remove_cvref_t<T> x) {
    { x.template getType<TYPE, DIG>() } -> same_as_or_convertible_to<TYPE&, CONVERT_TYPE>;
    { std::as_const(x).template getType<TYPE, DIG>() } -> same_as_or_convertible_to<const TYPE&, const CONVERT_TYPE>;
};

}  // namespace traits::helpers

template <typename T, typename TYPE>
concept type_able = traits::helpers::type_accessable<T, TYPE>;

template <typename T, typename TYPE>
concept getType_able = traits::helpers::get_type_accessable<T, TYPE>;

template <typename T, typename TYPE>
concept type_or_getType_able = type_able<T, TYPE> or getType_able<T, TYPE>;

template <typename T, typename TYPE, typename CONVERT_TYPE = void>
concept getType_template_able = traits::helpers::get_type_template_accessable<T, TYPE, CONVERT_TYPE>;

template <typename T, typename TYPE, typename CONVERT_TYPE = void>
concept CustomAccessType_able = traits::helpers::custom_type_accessable<T, TYPE, CONVERT_TYPE>;
