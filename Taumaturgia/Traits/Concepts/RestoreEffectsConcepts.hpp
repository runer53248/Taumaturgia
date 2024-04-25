#pragma once

class EffectTypeContainer;

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateMemberAccessableConcept(RestoreEffects, restoreEffects, EffectTypeContainer);
CreateGetAccessableConcept(RestoreEffects, EffectTypeContainer);
CreateCustomAccessableConcept(RestoreEffects, EffectTypeContainer);
CreateUserTypeAccessableConcept(RestoreEffects, EffectTypeContainer);
#else
template <typename T>
concept RestoreEffectsAccessable = requires(T x) {
    x.restoreEffects;
    std::is_same_v<decltype(T::restoreEffects), EffectTypeContainer>;
};

template <typename T>
concept GetRestoreEffectsAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getRestoreEffects() } -> same_as_ref<EffectTypeContainer>;
    { std::as_const(x).getRestoreEffects() } -> same_as_ref<const EffectTypeContainer>;
};

template <typename T>
struct CustomAccessRestoreEffects;

template <typename T>
concept CustomRestoreEffectsAccessable = requires(std::remove_cvref_t<T> x) {
    { CustomAccessRestoreEffects<T>::get(x) } -> same_as_ref<EffectTypeContainer>;
    { CustomAccessRestoreEffects<T>::get(std::as_const(x)) } -> same_as_ref<const EffectTypeContainer>;
};

template <typename T>
concept UserTypeRestoreEffectsAccessable = requires(std::remove_cvref_t<T> x) {
    { x.template getType<EffectTypeContainer>() } -> same_as_ref<EffectTypeContainer>;
    { std::as_const(x).template getType<EffectTypeContainer>() } -> same_as_ref<const EffectTypeContainer>;
};
#endif

}  // namespace traits
