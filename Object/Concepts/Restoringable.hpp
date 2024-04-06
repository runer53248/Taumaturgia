#pragma once
#include "Object/Concepts/Traits/RestoreEffectsTraits.hpp"
#include "Object/Concepts/Types/EffectTypeContainer.hpp"
#include "Object/Concepts/trait_accessable.hpp"

template <typename T>
concept Restoringable = trait_accessable<T, traits::accessRestoreEffects, EffectTypeContainer>;
