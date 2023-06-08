#pragma once
#include <type_traits>
#include "Traits/HealthTraits.hpp"
#include "Types/Health.hpp"

template <typename T>
concept Livingable = requires(T x) {
    traits::accessHealth::get(x);
    { traits::accessHealth::get(x) } -> std::convertible_to<Health>;
};
