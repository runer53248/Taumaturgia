#pragma once
#include "../Helpers/traits_helper.hpp"

namespace traits {

template <typename T, typename TYPE>
concept TypeAccessable = requires(T x) {
    x.type;
    std::is_same_v<decltype(T::type), TYPE>;
};

template <typename T, typename TYPE>
concept GetTypeAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getType() } -> same_as_ref<TYPE>;
    { std::as_const(x).getType() } -> same_as_ref<const TYPE>;
};

template <typename TYPE, typename T>
struct CustomAccessType;

template <typename T, typename TYPE>
concept CustomTypeAccessable = requires(std::remove_cvref_t<T> x) {
    { CustomAccessType<TYPE, std::remove_cvref_t<T>>::get(x) } -> same_as_ref<TYPE>;
    { CustomAccessType<TYPE, std::remove_cvref_t<T>>::get(std::as_const(x)) } -> same_as_ref<const TYPE>;
};

template <typename T, typename TYPE>
concept GetTypeTemplateAccessable = requires(std::remove_cvref_t<T> x) {
    { x.template getType<TYPE>() } -> same_as_ref<TYPE>;
    { std::as_const(x).template getType<TYPE>() } -> same_as_ref<const TYPE>;
};

}  // namespace traits
