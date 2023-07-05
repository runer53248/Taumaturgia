#pragma once
#include <type_traits>

struct EffectTypeContainer;

template <typename T>
concept RestoreEffectsAccessable = requires(T x) {
    x.restoreEffects;
    std::is_same_v<decltype(T::restoreEffects), EffectTypeContainer>;
};

template <typename T>
concept GetRestoreEffectsAccessable = requires(T x) {
    x.getRestoreEffects();
    { x.getRestoreEffects() } -> std::convertible_to<EffectTypeContainer>;
};

namespace traits {

template <typename T>
struct customAccessRestoreEffects {};

template <typename T>
concept CustomRestoreEffectsAccessable = requires(T x) {
    customAccessRestoreEffects<T>::get(x);
    { customAccessRestoreEffects<T>::get(x) } -> std::convertible_to<EffectTypeContainer>;
};

struct accessRestoreEffects {
    static auto& get(RestoreEffectsAccessable auto& el) {
        return el.restoreEffects;
    }

    static auto& get(GetRestoreEffectsAccessable auto& el) {
        return el.getRestoreEffects();
    }

    template <CustomRestoreEffectsAccessable T>
    static auto& get(T& el) {
        return customAccessRestoreEffects<std::remove_cv_t<T>>::get(el);
    }
};

}  // namespace traits
