#pragma once
#include "Helpers/traits_helper.hpp"
#include "Concepts/ArmorWearConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

#ifdef WITH_ADD_PROPERTIES

#include "UserTypeTraits.hpp"
template <typename T>
concept Wearingable = accessType_trait_able<T, WearContainer>;

using Wearingable_trait = traits::accessType<WearContainer>;

#else

namespace traits {

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

template <typename T>
concept Wearingable = trait_accessable<T, traits::accessArmorWear, WearContainer>;

using Wearingable_trait = traits::accessArmorWear;

#endif
