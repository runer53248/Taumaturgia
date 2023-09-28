#pragma once
#include <type_traits>
#include "Traits/DamageTraits.hpp"
#include "Types/Damage.hpp"

template <typename T>
concept Damagingable = requires(T x) {
    traits::accessDamage::get(x);
    { traits::accessDamage::get(x) } -> same_as_ref<Damage>;
};
