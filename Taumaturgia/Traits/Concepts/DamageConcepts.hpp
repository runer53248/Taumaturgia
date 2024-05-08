#pragma once
#include "../Helpers/traits_helper.hpp"

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
    { x.getDamage() } -> same_as_ref<Damage>;
    { std::as_const(x).getDamage() } -> same_as_ref<const Damage>;
};

template <typename T>
struct CustomAccessDamage;

template <typename T>
concept CustomDamageAccessable = requires(std::remove_cvref_t<T> x) {
    { CustomAccessDamage<T>::get(x) } -> same_as_ref<Damage>;
    { CustomAccessDamage<T>::get(std::as_const(x)) } -> same_as_ref<const Damage>;
};

template <typename T>
concept GetTypeTemplateDamageAccessable = requires(std::remove_cvref_t<T> x) {
    { x.template getType<Damage>() } -> same_as_ref<Damage>;
    { std::as_const(x).template getType<Damage>() } -> same_as_ref<const Damage>;
};
#endif

}  // namespace traits
