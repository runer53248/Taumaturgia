#pragma once

#include "Premade/Traits/accessArmorWear.hpp"
#include "Premade/Traits/accessCureHealth.hpp"
#include "Premade/Traits/accessDamage.hpp"
#include "Premade/Traits/accessHealth.hpp"
#include "Premade/Traits/accessProtection.hpp"
#include "Premade/Traits/accessRestoreEffects.hpp"

using Wearingable_trait = traits::accessArmorWear;
template <typename T>
concept Wearingable = trait_accessable<T, Wearingable_trait, WearContainer>;

using Healingable_trait = traits::accessCureHealth;
template <typename T>
concept Healingable = trait_accessable<T, Healingable_trait, CureHealth>;

using Damagingable_trait = traits::accessDamage;
template <typename T>
concept Damagingable = trait_accessable<T, Damagingable_trait, Damage>;

using Livingable_trait = traits::accessHealth;
template <typename T>
concept Livingable = trait_accessable<T, Livingable_trait, Health>;

using Protectingable_trait = traits::accessProtection;
template <typename T>
concept Protectingable = trait_accessable<T, Protectingable_trait, Protection>;

using Restoringable_trait = traits::accessRestoreEffects;
template <typename T>
concept Restoringable = trait_accessable<T, Restoringable_trait, EffectTypeContainer>;
