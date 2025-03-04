#pragma once
#include "Helpers/traits_helper.hpp"

namespace traits {

template <typename TYPE, typename T>
struct CustomAccessType;

}  // namespace traits

namespace traits::helpers {

template <typename T, typename TYPE>
concept TypeAccessable = requires(std::remove_cvref_t<T> x) {
    { x.type } -> std::same_as<TYPE&>;
    { std::as_const(x).type } -> std::same_as<const TYPE&>;
};

template <typename T, typename TYPE>
concept GetTypeAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getType() } -> std::same_as<TYPE&>;
    { std::as_const(x).getType() } -> std::same_as<const TYPE&>;
};

template <typename T, typename TYPE, typename CONVERT_TYPE = void>
concept CustomTypeAccessable = helpers::custom_type_trait_accessable<T, CustomAccessType, TYPE, CONVERT_TYPE>;

template <typename T, typename TYPE>
concept GetTypeTemplateAccessable = helpers::get_type_template_accessable<T, TYPE>;

}  // namespace traits::helpers
