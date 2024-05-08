#pragma once
#include "Concepts/RestoreEffectsConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

#ifdef WITH_ADD_PROPERTIES

#include "UserTypeTraits.hpp"
using Restoringable_trait = traits::accessType<EffectTypeContainer>;
template <typename T>
concept Restoringable = accessType_trait_able<T, EffectTypeContainer>;

#else

#include "Structs/accessRestoreEffects.hpp"
using Restoringable_trait = traits::accessRestoreEffects;
template <typename T>
concept Restoringable = trait_accessable<T, Restoringable_trait, EffectTypeContainer>;

#endif
