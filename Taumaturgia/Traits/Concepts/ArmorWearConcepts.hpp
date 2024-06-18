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
    { x.getArmorWear() } -> same_as_ref<WearContainer>;
    { std::as_const(x).getArmorWear() } -> same_as_ref<const WearContainer>;
};

template <typename T>
struct CustomAccessArmorWear;

template <typename T>
concept CustomArmorWearAccessable = requires(std::remove_cvref_t<T> x) {
    { CustomAccessArmorWear<T>::get(x) } -> same_as_ref<WearContainer>;
    { CustomAccessArmorWear<T>::get(std::as_const(x)) } -> same_as_ref<const WearContainer>;
};

template <typename T>
concept GetTypeTemplateArmorWearAccessable = requires(std::remove_cvref_t<T> x) {
    { x.template getType<WearContainer>() } -> same_as_ref<WearContainer>;
    { std::as_const(x).template getType<WearContainer>() } -> same_as_ref<const WearContainer>;
};
#endif

}  // namespace traits
