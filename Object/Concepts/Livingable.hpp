#pragma once
#include <type_traits>
#include "Traits/HealthTraits.hpp"
#include "Types/Health.hpp"

template <typename T>
concept Livingable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { traits::accessHealth::get(x) } -> same_as_ref<Health>;
    { traits::accessHealth::get(y) } -> same_as_ref<const Health>;
};
