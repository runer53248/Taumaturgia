#pragma once
#include "helper/same_as_ref.hpp"

struct EffectTypeContainer;

template <typename T>
concept RestoreEffectsAccessable = requires(T x) {
    x.restoreEffects;
    std::is_same_v<decltype(T::restoreEffects), EffectTypeContainer>;
};

template <typename T>
concept GetRestoreEffectsAccessable = requires(T x) {
    x.getRestoreEffects();
    { x.getRestoreEffects() } -> same_as_ref<EffectTypeContainer>;
};

namespace traits {

template <typename T>
struct CustomAccessRestoreEffects {};

template <typename T>
concept CustomRestoreEffectsAccessable = requires(T x) {
    CustomAccessRestoreEffects<T>::get(x);
    { CustomAccessRestoreEffects<T>::get(x) } -> same_as_ref<EffectTypeContainer>;
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
        return CustomAccessRestoreEffects<std::remove_cv_t<T>>::get(el);
    }
};

}  // namespace traits
