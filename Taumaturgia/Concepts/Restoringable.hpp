#pragma once
#include "Taumaturgia/Concepts/Helpers/trait_accessable.hpp"
#include "Taumaturgia/Concepts/Traits/RestoreEffectsTraits.hpp"
#include "Taumaturgia/Types/EffectTypeContainer.hpp"

template <typename T>
concept Restoringable = trait_accessable<T, traits::accessRestoreEffects, EffectTypeContainer>;
