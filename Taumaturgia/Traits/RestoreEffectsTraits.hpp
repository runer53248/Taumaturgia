#pragma once
#include "Helpers/traits_helper.hpp"
#include "Concepts/RestoreEffectsConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

#ifdef WITH_ADD_PROPERTIES

#include "UserTypeTraits.hpp"
template <typename T>
concept Restoringable = accessType_trait_able<T, EffectTypeContainer>;

using Restoringable_trait = traits::accessType<EffectTypeContainer>;

#else

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(RestoreEffects, restoreEffects, EffectTypeContainer);
#else
struct accessRestoreEffects {
    static constexpr auto& get(RestoreEffectsAccessable auto& el) noexcept {
        return el.restoreEffects;
    }

    template <GetRestoreEffectsAccessable T>
        requires(not(CustomRestoreEffectsAccessable<T> or UserTypeRestoreEffectsAccessable<T>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getRestoreEffects();
    }

    template <CustomRestoreEffectsAccessable T>
        requires(not UserTypeRestoreEffectsAccessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessRestoreEffects<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeRestoreEffectsAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<EffectTypeContainer>();
    }
};
#endif

}  // namespace traits

template <typename T>
concept Restoringable = trait_accessable<T, traits::accessRestoreEffects, EffectTypeContainer>;

using Restoringable_trait = traits::accessRestoreEffects;

#endif
