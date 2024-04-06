#pragma once
#include <type_traits>

template <typename T, typename TRAIT, typename RESULT_TYPE>
concept trait_accessible = requires(std::remove_cvref_t<T> x) {
    { TRAIT::get(x) } -> same_as_ref<RESULT_TYPE>;
    { TRAIT::get(std::as_const(x)) } -> same_as_ref<const RESULT_TYPE>;
};
