#pragma once
#include "helper/traits_helper.hpp"

struct WearContainer;

namespace traits {

CreateAccessableConcept(ArmorWear, armorWear, WearContainer);
CreateGetAccessableConcept(ArmorWear, WearContainer);
CreateCustomAccessableConcept(ArmorWear, WearContainer);
CreateUserTypeAccessableConcept(ArmorWear, WearContainer);

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(ArmorWear, armorWear, WearContainer);
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
        return el.template getType<WearContainer>();
    }
};
#endif

}  // namespace traits
