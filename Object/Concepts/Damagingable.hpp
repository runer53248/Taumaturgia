#pragma once
#include "Object/Concepts/Traits/DamageTraits.hpp"
#include "Object/Concepts/Types/Damage.hpp"
#include "Object/Concepts/trait_accessable.hpp"

template <typename T>
concept Damagingable = trait_accessable<T, traits::accessDamage, Damage>;
