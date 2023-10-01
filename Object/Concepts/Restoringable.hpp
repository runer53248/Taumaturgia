#pragma once
#include <type_traits>
#include "Traits/RestoreEffectsTraits.hpp"
#include "Types/EffectTypeContainer.hpp"

template <typename T>
concept Restoringable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { traits::accessRestoreEffects::get(x) } -> same_as_ref<EffectTypeContainer>;
    { traits::accessRestoreEffects::get(y) } -> same_as_ref<const EffectTypeContainer>;
};
