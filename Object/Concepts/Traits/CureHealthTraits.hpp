#pragma once
#include <utility>  // for as_const
#include "helper/same_as_ref.hpp"
#include "helper/traits_helper.hpp"

struct CureHealth;

namespace traits {

CreateAccessableConcept(CureHealth, cureHealth, CureHealth);
CreateGetAccessableConcept(CureHealth, CureHealth);
CreateCustomAccessableConcept(CureHealth, CureHealth);
CreateUserTypeAccessableConcept(CureHealth, CureHealth);

struct accessCureHealth {
    static auto& get(CureHealthAccessable auto& el) {
        return el.cureHealth;
    }

    template <GetCureHealthAccessable T>
        requires(not(CustomCureHealthAccessable<T> or UserTypeCureHealthAccessable<T>))
    static decltype(auto) get(T& el) {
        return el.getCureHealth();
    }

    template <CustomCureHealthAccessable T>
        requires(not UserTypeCureHealthAccessable<T>)
    static decltype(auto) get(T& el) {
        return CustomAccessCureHealth<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeCureHealthAccessable T>
    static decltype(auto) get(T& el) {
        return el.template getType<CureHealth>();
    }
};

}  // namespace traits
