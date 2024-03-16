#pragma once
#include "helper/traits_helper.hpp"

struct ProtectionContainer;

namespace traits {

CreateAccessableConcept(ArmorWear, armorWear, ProtectionContainer);
CreateGetAccessableConcept(ArmorWear, ProtectionContainer);
CreateCustomAccessableConcept(ArmorWear, ProtectionContainer);
CreateUserTypeAccessableConcept(ArmorWear, ProtectionContainer);

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(ArmorWear, armorWear, ProtectionContainer);
#else
struct accessArmorWear {
    static auto& get(ArmorWearAccessable auto& el) noexcept {
        return el.armorWear;
    }

    template <GetArmorWearAccessable T>
        requires(not(CustomArmorWearAccessable<T> or UserTypeArmorWearAccessable<T>))
    static decltype(auto) get(T& el) noexcept {
        return el.getArmorWear();
    }

    template <CustomArmorWearAccessable T>
        requires(not UserTypeArmorWearAccessable<T>)
    static decltype(auto) get(T& el) noexcept {
        return CustomAccessArmorWear<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeArmorWearAccessable T>
    static decltype(auto) get(T& el) noexcept {
        return el.template getType<ProtectionContainer>();
    }
};
#endif

}  // namespace traits
