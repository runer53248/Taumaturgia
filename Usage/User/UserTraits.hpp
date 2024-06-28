#pragma once
#include "Taumaturgia/Traits/Helpers/traits_helper.hpp"
#include "Taumaturgia/Traits/UserTypeTraits.hpp"
#include "Usage/Concepts/Concepts.hpp"

#include "Usage/Traits/accessName.hpp"

using Damagingable_trait = traits::accessType<Damage>;
using Healingable_trait = traits::accessType<CureHealth>;
using Livingable_trait = traits::accessType<Health>;
using Protectingable_trait = traits::accessType<Protection>;
using Restoringable_trait = traits::accessType<EffectTypeContainer>;
using Wearingable_trait = traits::accessType<WearContainer>;
using Namingable_trait = traits::accessName;
