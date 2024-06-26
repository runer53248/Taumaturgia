#pragma once
#include "Taumaturgia/Traits/Helpers/traits_helper.hpp"

#include "Traits/accessArmorWear.hpp"
#include "Traits/accessCureHealth.hpp"
#include "Traits/accessDamage.hpp"
#include "Traits/accessHealth.hpp"
#include "Traits/accessProtection.hpp"
#include "Traits/accessRestoreEffects.hpp"

using Damagingable_trait = traits::accessDamage;
using Healingable_trait = traits::accessCureHealth;
using Livingable_trait = traits::accessHealth;
using Protectingable_trait = traits::accessProtection;
using Restoringable_trait = traits::accessRestoreEffects;
using Wearingable_trait = traits::accessArmorWear;
