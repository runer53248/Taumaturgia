#pragma once
#include "helper/traits_helper.hpp"

struct Damage;

namespace traits {

CreateAccessableConcept(Damage, dmg, Damage);
CreateGetAccessableConcept(Damage, Damage);
CreateCustomAccessableConcept(Damage, Damage);
CreateUserTypeAccessableConcept(Damage, Damage);

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(Damage, dmg, Damage);
#else
struct accessDamage {
    static auto& get(DamageAccessable auto& el) {
        return el.dmg;
    }

    template <GetDamageAccessable T>
        requires(not(CustomDamageAccessable<T> or UserTypeDamageAccessable<T>))
    static decltype(auto) get(T& el) {
        return el.getDamage();
    }

    template <CustomDamageAccessable T>
        requires(not UserTypeDamageAccessable<T>)
    static decltype(auto) get(T& el) {
        return CustomAccessDamage<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeDamageAccessable T>
    static decltype(auto) get(T& el) {
        return el.template getType<Damage>();
    }
};
#endif

}  // namespace traits
