#pragma once
#include <type_traits>
#include "Traits/CureHealthTraits.hpp"
#include "Types/Health.hpp"

template <typename T>
concept Healingable = requires(T x) {
    traits::accessCureHealth::get(x);
    { traits::accessCureHealth::get(x) } -> same_as_ref<Health>;
};
