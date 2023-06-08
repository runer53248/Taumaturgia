#pragma once
#include <type_traits>
#include "Traits/RestoreEffectsTraits.hpp"
#include "Types/EffectTypeContainer.hpp"

template <typename T>
concept Restoringable = requires(T x) {
    traits::accessRestoreEffects::get(x);
    { traits::accessRestoreEffects::get(x) } -> std::convertible_to<EffectTypeContainer>;
};
