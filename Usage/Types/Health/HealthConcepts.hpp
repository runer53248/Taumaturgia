#pragma once
#include "Taumaturgia/Traits/Helpers/traits_helper.hpp"

class Health;

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateMemberAccessableConcept(Health, hp, Health);
CreateGetAccessableConcept(Health, Health);
CreateCustomAccessableConcept(Health, Health);
CreateGetTypeTemplateAccessableConcept(Health, Health);
#else
template <typename T>
concept HealthAccessable = requires(T x) {
    x.hp;
    std::is_same_v<decltype(T::hp), Health>;
};

template <typename T>
concept GetHealthAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getHealth() } -> std::same_as<Health&>;
    { std::as_const(x).getHealth() } -> std::same_as<const Health&>;
};

#endif

}  // namespace traits
