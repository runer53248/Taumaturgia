#pragma once
#include <type_traits>
#include "Traits/CureHealthTraits.hpp"
#include "Types/Health.hpp"

template <typename T>
concept Healingable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { traits::accessCureHealth::get(x) } -> same_as_ref<Health>;
    { traits::accessCureHealth::get(y) } -> same_as_ref<const Health>;
};
