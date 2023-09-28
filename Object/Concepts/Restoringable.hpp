#pragma once
#include <type_traits>
#include "Traits/RestoreEffectsTraits.hpp"
#include "Types/EffectTypeContainer.hpp"

template <typename T>
concept Restoringable = requires(T x) {
    traits::accessRestoreEffects::get(x);
    { traits::accessRestoreEffects::get(x) } -> same_as_ref<EffectTypeContainer>;
};
