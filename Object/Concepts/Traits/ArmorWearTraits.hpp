#pragma once
#include <utility>  // for as_const
#include "helper/same_as_ref.hpp"
#include "helper/traits_helper.hpp"

struct ProtectionContainer;

namespace traits {

CreateAccessableConcept(ArmorWear, armorWear, ProtectionContainer);
CreateGetAccessableConcept(ArmorWear, ProtectionContainer);
CreateCustomAccessableConcept(ArmorWear, ProtectionContainer);
CreateUserTypeAccessableConcept(ArmorWear, ProtectionContainer);

struct accessArmorWear {
    static auto& get(ArmorWearAccessable auto& el) {
        return el.armorWear;
    }

    template <GetArmorWearAccessable T>
        requires(not(CustomArmorWearAccessable<T> or UserTypeArmorWearAccessable<T>))
    static decltype(auto) get(T& el) {
        return el.getArmorWear();
    }

    template <CustomArmorWearAccessable T>
        requires(not UserTypeArmorWearAccessable<T>)
    static decltype(auto) get(T& el) {
        return CustomAccessArmorWear<std::remove_cv_t<T>>::get(el);
    }

    template <UserTypeArmorWearAccessable T>
    static decltype(auto) get(T& el) {
        return el.template getType<ProtectionContainer>();
    }
};

}  // namespace traits
