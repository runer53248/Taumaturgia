#pragma once
#include <type_traits>
#include "Traits/ProtectionTraits.hpp"
#include "Types/Protection.hpp"

template <typename T>
concept Protectingable = requires(std::remove_cvref_t<T> x) {
    { traits::accessProtection::get(x) } -> same_as_ref<Protection>;
    { traits::accessProtection::get(std::as_const(x)) } -> same_as_ref<const Protection>;
};
