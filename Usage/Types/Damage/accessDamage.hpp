#pragma once
#include "Usage/Types/Damage/DamageConcepts.hpp"

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(Damage, dmg, Damage);
#else
struct accessDamage {
    template <typename T>
    static const bool accessable = helpers::trait_accessable<T, accessDamage, Damage>;

    static constexpr auto& get(DamageAccessable auto& el) noexcept {
        return el.dmg;
    }

    template <GetDamageAccessable T>
        requires(not(CustomDamageAccessable<T> or GetTypeTemplateDamageAccessable<T>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getDamage();
    }

    template <CustomDamageAccessable T>
        requires(not GetTypeTemplateDamageAccessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessDamage<std::remove_cvref_t<T>>::get(el);
    }

    template <GetTypeTemplateDamageAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<Damage>();
    }
};
#endif

}  // namespace traits
