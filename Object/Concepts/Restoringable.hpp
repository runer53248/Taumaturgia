#pragma once
#include <type_traits>
#include "Types/EffectTypeContainer.hpp"

template <typename T>
concept Restoringable = requires (T x) {
    x.restoreEffects;
    std::is_same_v<decltype(T::restoreEffects), EffectTypeContainer>;
};
