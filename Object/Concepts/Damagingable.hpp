#pragma once
#include <type_traits>
#include "Traits/DamageTraits.hpp"
#include "Types/Damage.hpp"

template <typename T>
concept Damagingable = requires(std::remove_cvref_t<T> x) {
    { traits::accessDamage::get(x) } -> same_as_ref<Damage>;
    { traits::accessDamage::get(std::as_const(x)) } -> same_as_ref<const Damage>;
};
