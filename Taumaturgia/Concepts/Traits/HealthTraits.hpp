#pragma once
#include "Helpers/traits_helper.hpp"

struct Health;

namespace traits {

CreateAccessableConcept(Health, hp, Health);
CreateGetAccessableConcept(Health, Health);
CreateCustomAccessableConcept(Health, Health);
CreateUserTypeAccessableConcept(Health, Health);

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(Health, hp, Health);
#else
struct accessHealth {
    static auto& get(HealthAccessable auto& el) noexcept {
        return el.hp;
    }

    template <GetHealthAccessable T>
        requires(not(CustomHealthAccessable<T> or UserTypeHealthAccessable<T>))
    static decltype(auto) get(T& el) noexcept {
        return el.getHealth();
    }

    template <CustomHealthAccessable T>
        requires(not UserTypeHealthAccessable<T>)
    static decltype(auto) get(T& el) noexcept {
        return CustomAccessHealth<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeHealthAccessable T>
    static decltype(auto) get(T& el) noexcept {
        return el.template getType<Health>();
    }
};
#endif

}  // namespace traits
