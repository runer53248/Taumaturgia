#pragma once
#include <type_traits>
#include "Traits/ProtectionTraits.hpp"
#include "Types/Protection.hpp"

template <typename T>
concept Protectingable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { traits::accessProtection::get(x) } -> same_as_ref<Protection>;
    { traits::accessProtection::get(y) } -> same_as_ref<const Protection>;
};
