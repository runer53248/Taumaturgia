#pragma once
#include "Taumaturgia/Traits/Helpers/traits_helper.hpp"

class Damage;

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateMemberAccessableConcept(Damage, dmg, Damage);
CreateGetAccessableConcept(Damage, Damage);
CreateCustomAccessableConcept(Damage, Damage);
CreateGetTypeTemplateAccessableConcept(Damage, Damage);
#else
template <typename T>
concept DamageAccessable = requires(T x) {
    x.dmg;
    std::is_same_v<decltype(T::dmg), Damage>;
};

template <typename T>
concept GetDamageAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getDamage() } -> std::same_as<Damage&>;
    { std::as_const(x).getDamage() } -> std::same_as<const Damage&>;
};

template <typename T>
struct CustomAccessDamage;

template <typename T>
concept CustomDamageAccessable = helpers::custom_trait_accessable<T, CustomAccessDamage, Damage>;

template <typename T>
concept GetTypeTemplateDamageAccessable = helpers::get_type_template_accessable<T, Damage>;
#endif

}  // namespace traits
