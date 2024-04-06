#pragma once
#include "Helpers/traits_helper.hpp"

struct CureHealth;

namespace traits {

CreateAccessableConcept(CureHealth, cureHealth, CureHealth);
CreateGetAccessableConcept(CureHealth, CureHealth);
CreateCustomAccessableConcept(CureHealth, CureHealth);
CreateUserTypeAccessableConcept(CureHealth, CureHealth);

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(CureHealth, cureHealth, CureHealth);
#else
struct accessCureHealth {
    static auto& get(CureHealthAccessable auto& el) noexcept{
        return el.cureHealth;
    }

    template <GetCureHealthAccessable T>
        requires(not(CustomCureHealthAccessable<T> or UserTypeCureHealthAccessable<T>))
    static decltype(auto) get(T& el) noexcept {
        return el.getCureHealth();
    }

    template <CustomCureHealthAccessable T>
        requires(not UserTypeCureHealthAccessable<T>)
    static decltype(auto) get(T& el) noexcept{
        return CustomAccessCureHealth<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeCureHealthAccessable T>
    static decltype(auto) get(T& el) noexcept {
        return el.template getType<CureHealth>();
    }
};
#endif

}  // namespace traits
