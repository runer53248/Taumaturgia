#pragma once
#include <type_traits>
#include "Traits/HealthTraits.hpp"
#include "Types/Health.hpp"

template <typename T>
concept Livingable = requires(std::remove_cvref_t<T> x) {
    { traits::accessHealth::get(x) } -> same_as_ref<Health>;
    { traits::accessHealth::get(std::as_const(x)) } -> same_as_ref<const Health>;
};
