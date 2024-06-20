#pragma once
#include "Taumaturgia/Traits/Helpers/traits_helper.hpp"

class EffectTypeContainer;

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateMemberAccessableConcept(RestoreEffects, restoreEffects, EffectTypeContainer);
CreateGetAccessableConcept(RestoreEffects, EffectTypeContainer);
CreateCustomAccessableConcept(RestoreEffects, EffectTypeContainer);
CreateGetTypeTemplateAccessableConcept(RestoreEffects, EffectTypeContainer);
#else
template <typename T>
concept RestoreEffectsAccessable = requires(T x) {
    x.restoreEffects;
    std::is_same_v<decltype(T::restoreEffects), EffectTypeContainer>;
};

template <typename T>
concept GetRestoreEffectsAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getRestoreEffects() } -> std::same_as<EffectTypeContainer&>;
    { std::as_const(x).getRestoreEffects() } -> std::same_as<const EffectTypeContainer&>;
};

template <typename T>
struct CustomAccessRestoreEffects;

template <typename T>
concept CustomRestoreEffectsAccessable = helpers::custom_trait_accessable<T, CustomAccessRestoreEffects, EffectTypeContainer>;

template <typename T>
concept GetTypeTemplateRestoreEffectsAccessable = helpers::get_type_template_accessable<T, EffectTypeContainer>;
#endif

}  // namespace traits
