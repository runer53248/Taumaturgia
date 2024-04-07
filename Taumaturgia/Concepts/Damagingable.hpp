#pragma once
#include "Taumaturgia/Concepts/Helpers/trait_accessable.hpp"
#include "Taumaturgia/Concepts/Traits/DamageTraits.hpp"
#include "Taumaturgia/Types/Damage.hpp"

template <typename T>
concept Damagingable = trait_accessable<T, traits::accessDamage, Damage>;
