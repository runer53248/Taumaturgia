#pragma once
#include "Object/Concepts/Helpers/trait_accessable.hpp"
#include "Object/Concepts/Traits/DamageTraits.hpp"
#include "Object/Concepts/Types/Damage.hpp"

template <typename T>
concept Damagingable = trait_accessable<T, traits::accessDamage, Damage>;
