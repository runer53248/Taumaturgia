#pragma once
#include "Helpers/traits_helper.hpp"
#include "Concepts/DamageConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

#ifdef WITH_ADD_PROPERTIES

#include "UserTypeTraits.hpp"
template <typename T>
concept Damagingable = accessType_trait_able<T, Damage>;

using Damagingable_trait = traits::accessType<Damage>;

#else

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(Damage, dmg, Damage);
#else
struct accessDamage {
    static constexpr auto& get(DamageAccessable auto& el) noexcept {
        return el.dmg;
    }

    template <GetDamageAccessable T>
        requires(not(CustomDamageAccessable<T> or UserTypeDamageAccessable<T>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getDamage();
    }

    template <CustomDamageAccessable T>
        requires(not UserTypeDamageAccessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessDamage<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeDamageAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<Damage>();
    }
};
#endif

}  // namespace traits

using Damagingable_trait = traits::accessDamage;

template <typename T>
concept Damagingable = trait_accessable<T, Damagingable_trait, Damage>;

#endif
