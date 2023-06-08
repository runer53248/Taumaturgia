#pragma once
#include <type_traits>
#include "Traits/ProtectionTraits.hpp"
#include "Types/Protection.hpp"

template <typename T>
concept Protectingable = requires(T x) {
    traits::accessProtection::get(x);
    { traits::accessProtection::get(x) } -> std::convertible_to<Protection>;
};
