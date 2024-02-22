#pragma once
#include <utility>  // for as_const
#include "helper/same_as_ref.hpp"
#include "helper/traits_helper.hpp"

struct EffectTypeContainer;

namespace traits {

CreateAccessableConcept(RestoreEffects, restoreEffects, EffectTypeContainer);
CreateGetAccessableConcept(RestoreEffects, EffectTypeContainer);
CreateCustomAccessableConcept(RestoreEffects, EffectTypeContainer);
CreateUserTypeAccessableConcept(RestoreEffects, EffectTypeContainer);

struct accessRestoreEffects {
    static auto& get(RestoreEffectsAccessable auto& el) {
        return el.restoreEffects;
    }

    template <GetRestoreEffectsAccessable T>
        requires(not(CustomRestoreEffectsAccessable<T> or UserTypeRestoreEffectsAccessable<T>))
    static decltype(auto) get(T& el) {
        return el.getRestoreEffects();
    }

    template <CustomRestoreEffectsAccessable T>
        requires(not UserTypeRestoreEffectsAccessable<T>)
    static decltype(auto) get(T& el) {
        return CustomAccessRestoreEffects<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeRestoreEffectsAccessable T>
    static decltype(auto) get(T& el) {
        return el.template getType<EffectTypeContainer>();
    }
};

}  // namespace traits
