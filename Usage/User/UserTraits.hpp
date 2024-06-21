#pragma once
#include "Taumaturgia/Traits/Helpers/traits_helper.hpp"
#include "Taumaturgia/Traits/UserTypeTraits.hpp"

#include "Usage/Concepts/Concepts.hpp"

using Wearingable_trait = traits::accessType<WearContainer>;
using Healingable_trait = traits::accessType<CureHealth>;
using Damagingable_trait = traits::accessType<Damage>;
using Livingable_trait = traits::accessType<Health>;
using Protectingable_trait = traits::accessType<Protection>;
using Restoringable_trait = traits::accessType<EffectTypeContainer>;
