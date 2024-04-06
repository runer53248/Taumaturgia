#pragma once
#include "Object/Concepts/Helpers/trait_accessable.hpp"
#include "Object/Concepts/Traits/RestoreEffectsTraits.hpp"
#include "Object/Concepts/Types/EffectTypeContainer.hpp"

template <typename T>
concept Restoringable = trait_accessable<T, traits::accessRestoreEffects, EffectTypeContainer>;
