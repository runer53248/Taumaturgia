#pragma once
#include "Taumaturgia/Traits/trait.hpp"
#include "Usage/Types/EffectTypeContainer/RestoreEffectsConcepts.hpp"

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(RestoreEffects, restoreEffects, EffectTypeContainer);
#else
struct accessRestoreEffects : public impl::accessType<EffectTypeContainer> {
    template <typename T>
    static const bool accessable = helpers::trait_accessable<T, accessRestoreEffects, EffectTypeContainer>;

    template <RestoreEffectsAccessable T>
    requires(not accessType<EffectTypeContainer>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.restoreEffects);
    }

    template <GetRestoreEffectsAccessable T>
    requires(not accessType<EffectTypeContainer>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getRestoreEffects();
    }

    using accessType<EffectTypeContainer>::get;
};
#endif

}  // namespace traits

template <>
struct trait_<EffectTypeContainer> {
    using type = traits::accessRestoreEffects;
};
