#pragma once
#include "Taumaturgia/Traits/Helpers/traits_helper.hpp"

namespace traits {

template <typename T, typename TYPE>
concept TypeAccessable = requires(T x) {
    x.type;
    std::is_same_v<decltype(T::type), TYPE>;
};

template <typename T, typename TYPE>
concept GetTypeAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getType() } -> std::same_as<TYPE&>;
    { std::as_const(x).getType() } -> std::same_as<const TYPE&>;
};

template <typename TYPE, typename T>
struct CustomAccessType;

template <typename T, typename TYPE>
concept CustomTypeAccessable = helpers::custom_type_trait_accessable<T, CustomAccessType, TYPE>;

template <typename T, typename TYPE>
concept GetTypeTemplateAccessable = helpers::get_type_template_accessable<T, TYPE>;

}  // namespace traits
