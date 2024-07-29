#pragma once
#include "Taumaturgia/Traits/accessType.hpp"
#include "Usage/Types/Damage/DamageConcepts.hpp"

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(Damage, dmg, Damage);
#else
struct accessDamage : public accessType<Damage> {
    template <typename T>
    static constexpr bool accessable = helpers::trait_accessable<T, accessDamage, Damage>;

    template <DamageAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.dmg);
    }

    template <GetDamageAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getDamage();
    }

    using accessType<Damage>::get;
};
#endif

}  // namespace traits
