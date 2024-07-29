#pragma once
#include "Taumaturgia/Traits/Helpers/traits_helper.hpp"

class WearContainer;

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateMemberAccessableConcept(ArmorWear, armorWear, WearContainer);
CreateGetAccessableConcept(ArmorWear, WearContainer);
CreateCustomAccessableConcept(ArmorWear, WearContainer);
CreateGetTypeTemplateAccessableConcept(ArmorWear, WearContainer);
#else
template <typename T>
concept ArmorWearAccessable = requires(T x) {
    x.armorWear;
    std::is_same_v<decltype(T::armorWear), WearContainer>;
};

template <typename T>
concept GetArmorWearAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getArmorWear() } -> std::same_as<WearContainer&>;
    { std::as_const(x).getArmorWear() } -> std::same_as<const WearContainer&>;
};

#endif

}  // namespace traits
