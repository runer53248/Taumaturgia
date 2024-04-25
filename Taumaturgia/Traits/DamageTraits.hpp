#pragma once
#include "Helpers/traits_helper.hpp"
#include "Concepts/DamageConcepts.hpp"

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(Damage, dmg, Damage);
#else
struct accessDamage {
    static auto& get(DamageAccessable auto& el) noexcept {
        return el.dmg;
    }

    template <GetDamageAccessable T>
        requires(not(CustomDamageAccessable<T> or UserTypeDamageAccessable<T>))
    static decltype(auto) get(T& el) noexcept {
        return el.getDamage();
    }

    template <CustomDamageAccessable T>
        requires(not UserTypeDamageAccessable<T>)
    static decltype(auto) get(T& el) noexcept {
        return CustomAccessDamage<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeDamageAccessable T>
    static decltype(auto) get(T& el) noexcept {
        return el.template getType<Damage>();
    }
};
#endif

}  // namespace traits
