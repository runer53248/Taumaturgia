#pragma once
#include "helper/traits_helper.hpp"

struct Protection;

namespace traits {

CreateAccessableConcept(Protection, protection, Protection);
CreateGetAccessableConcept(Protection, Protection);
CreateCustomAccessableConcept(Protection, Protection);
CreateUserTypeAccessableConcept(Protection, Protection);

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(Protection, protection, Protection);
#else
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
        return CustomAccessProtection<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeProtectionAccessable T>
    static decltype(auto) get(T& el) {
        return el.template getType<Protection>();
    }
};
#endif

}  // namespace traits
