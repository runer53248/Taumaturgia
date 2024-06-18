#pragma once
#include "Taumaturgia/Traits/Concepts/RestoreEffectsConcepts.hpp"

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(RestoreEffects, restoreEffects, EffectTypeContainer);
#else
struct accessRestoreEffects {
    static constexpr auto& get(RestoreEffectsAccessable auto& el) noexcept {
        return el.restoreEffects;
    }

    template <GetRestoreEffectsAccessable T>
        requires(not(CustomRestoreEffectsAccessable<T> or GetTypeTemplateRestoreEffectsAccessable<T>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getRestoreEffects();
    }

    template <CustomRestoreEffectsAccessable T>
        requires(not GetTypeTemplateRestoreEffectsAccessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessRestoreEffects<std::remove_cvref_t<T> >::get(el);
    }

    template <GetTypeTemplateRestoreEffectsAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<EffectTypeContainer>();
    }
};
#endif

}  // namespace traits
