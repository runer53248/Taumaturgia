#pragma once
#include <utility>  // for as_const
#include "helper/same_as_ref.hpp"
#include "helper/traits_helper.hpp"

struct Protection;

namespace traits {

CreateAccessableConcept(Protection, protection, Protection);
CreateGetAccessableConcept(Protection, Protection);
CreateCustomAccessableConcept(Protection, Protection);
CreateUserTypeAccessableConcept(Protection, Protection);

struct accessProtection {
    static auto& get(ProtectionAccessable auto& el) {
        return el.protection;
    }

    template <GetProtectionAccessable T>
        requires(not(CustomProtectionAccessable<T> or UserTypeProtectionAccessable<T>))
    static decltype(auto) get(T& el) {
        return el.getProtection();
    }

    template <CustomProtectionAccessable T>
        requires(not UserTypeProtectionAccessable<T>)
    static decltype(auto) get(T& el) {
        return CustomAccessProtection<std::remove_cv_t<T>>::get(el);
    }

    template <UserTypeProtectionAccessable T>
    static decltype(auto) get(T& el) {
        return el.template getType<Protection>();
    }
};

}  // namespace traits
