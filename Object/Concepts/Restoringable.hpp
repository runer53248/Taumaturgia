#pragma once
#include <type_traits>
#include "Traits/RestoreEffectsTraits.hpp"
#include "Types/EffectTypeContainer.hpp"

template <typename T>
concept Restoringable = requires(std::remove_cvref_t<T> x) {
    { traits::accessRestoreEffects::get(x) } -> same_as_ref<EffectTypeContainer>;
    { traits::accessRestoreEffects::get(std::as_const(x)) } -> same_as_ref<const EffectTypeContainer>;
};
