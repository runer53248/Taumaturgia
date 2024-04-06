#pragma once
#include "Object/Concepts/Traits/DamageTraits.hpp"
#include "Object/Concepts/Types/Damage.hpp"
#include "Object/Concepts/trait_accessible.hpp"

template <typename T>
concept Damagingable = trait_accessible<T, traits::accessDamage, Damage>;
