#pragma once
#include <type_traits>
#include "Traits/DamageTraits.hpp"
#include "Types/Damage.hpp"

template <typename T>
concept Damagingable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { traits::accessDamage::get(x) } -> same_as_ref<Damage>;
    { traits::accessDamage::get(y) } -> same_as_ref<const Damage>;
};
