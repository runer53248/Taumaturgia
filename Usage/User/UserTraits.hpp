#pragma once
#include "Taumaturgia/Traits/Helpers/trait_accessable.hpp"
#include "Taumaturgia/Traits/UserTypeTraits.hpp"

using Wearingable_trait = traits::accessType<WearContainer>;
template <typename T>
concept Wearingable = accessType_trait_able<T, WearContainer>;

using Healingable_trait = traits::accessType<CureHealth>;
template <typename T>
concept Healingable = accessType_trait_able<T, CureHealth>;

using Damagingable_trait = traits::accessType<Damage>;
template <typename T>
concept Damagingable = accessType_trait_able<T, Damage>;

using Livingable_trait = traits::accessType<Health>;
template <typename T>
concept Livingable = accessType_trait_able<T, Health>;

using Protectingable_trait = traits::accessType<Protection>;
template <typename T>
concept Protectingable = accessType_trait_able<T, Protection>;

using Restoringable_trait = traits::accessType<EffectTypeContainer>;
template <typename T>
concept Restoringable = accessType_trait_able<T, EffectTypeContainer>;
