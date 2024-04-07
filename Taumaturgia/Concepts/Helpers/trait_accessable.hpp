#pragma once
#include <utility>  // for as_const
#include "Taumaturgia/Traits/Helpers/same_as_ref.hpp"

template <typename T, typename TRAIT, typename RESULT_TYPE>
concept trait_accessable = requires(std::remove_cvref_t<T> x) {
    { TRAIT::get(x) } -> same_as_ref<RESULT_TYPE>;
    { TRAIT::get(std::as_const(x)) } -> same_as_ref<const RESULT_TYPE>;
};

template <typename T, typename TRAIT, typename RESULT_TYPE>
concept trait_access_covertable = requires(std::remove_cvref_t<T> x) {
    { TRAIT::get(x) } -> std::convertible_to<RESULT_TYPE>;
    { TRAIT::get(std::as_const(x)) } -> std::convertible_to<const RESULT_TYPE>;
};
