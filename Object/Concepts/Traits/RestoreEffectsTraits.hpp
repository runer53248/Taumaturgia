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
    template <RestoreEffectsAccessable T>
    static auto& get(T& el) {
        return el.restoreEffects;
    }

    template <GetRestoreEffectsAccessable T>
    static auto& get(T& el) {
        return el.getRestoreEffects();
    }

    template <CustomRestoreEffectsAccessable T>
    static auto& get(T& el) {
        return customAccessRestoreEffects<T>::get(el);
    }

    template <CustomRestoreEffectsAccessable T>
    static auto& get(const T& el) {
        return customAccessRestoreEffects<T>::get(el);
    }
};

}  // namespace traits
