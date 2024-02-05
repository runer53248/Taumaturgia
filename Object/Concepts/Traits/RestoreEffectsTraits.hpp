#pragma once
#include "helper/same_as_ref.hpp"

struct EffectTypeContainer;

namespace traits {

template <typename T>
concept RestoreEffectsAccessable = requires(T x) {
    x.restoreEffects;
    std::is_same_v<decltype(T::restoreEffects), EffectTypeContainer>;
};

template <typename T>
concept GetRestoreEffectsAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { x.getRestoreEffects() } -> same_as_ref<EffectTypeContainer>;
    { y.getRestoreEffects() } -> same_as_ref<const EffectTypeContainer>;
};

template <typename T>
struct CustomAccessRestoreEffects {};

template <typename T>
concept CustomRestoreEffectsAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { CustomAccessRestoreEffects<T>::get(x) } -> same_as_ref<EffectTypeContainer>;
    { CustomAccessRestoreEffects<T>::get(y) } -> same_as_ref<const EffectTypeContainer>;
};

template <typename T>
concept UserTypeRestoreEffectsAccessable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { x.template getType<EffectTypeContainer>() } -> same_as_ref<EffectTypeContainer>;
    { y.template getType<EffectTypeContainer>() } -> same_as_ref<const EffectTypeContainer>;
};

struct accessRestoreEffects {
    static auto& get(RestoreEffectsAccessable auto& el) {
        return el.restoreEffects;
    }

    template <GetRestoreEffectsAccessable T>
        requires(not CustomRestoreEffectsAccessable<T> and not UserTypeRestoreEffectsAccessable<T>)
    static decltype(auto) get(T& el) {
        return el.getRestoreEffects();
    }

    template <CustomRestoreEffectsAccessable T>
        requires(not UserTypeRestoreEffectsAccessable<T>)
    static decltype(auto) get(T& el) {
        return CustomAccessRestoreEffects<std::remove_cv_t<T>>::get(el);
    }

    template <CustomRestoreEffectsAccessable T>
        requires(not UserTypeRestoreEffectsAccessable<T>)
    static decltype(auto) get(const T& el) {
        return CustomAccessRestoreEffects<std::remove_cv_t<T>>::get(el);
    }

    template <UserTypeRestoreEffectsAccessable T>
    static decltype(auto) get(T& el) {
        return el.template getType<EffectTypeContainer>();
    }

    template <UserTypeRestoreEffectsAccessable T>
    static decltype(auto) get(const T& el) {
        return el.template getType<EffectTypeContainer>();
    }
};

}  // namespace traits
