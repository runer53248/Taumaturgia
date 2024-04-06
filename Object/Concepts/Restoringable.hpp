#pragma once
#include "Object/Concepts/Traits/RestoreEffectsTraits.hpp"
#include "Object/Concepts/Types/EffectTypeContainer.hpp"
#include "Object/Concepts/trait_accessible.hpp"

template <typename T>
concept Restoringable = trait_accessible<T, traits::accessRestoreEffects, EffectTypeContainer>;
