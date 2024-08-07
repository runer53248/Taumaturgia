#pragma once
#include "Taumaturgia/Traits/Helpers/traits_helper.hpp"

class CureHealth;

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateMemberAccessableConcept(CureHealth, cureHealth, CureHealth);
CreateGetAccessableConcept(CureHealth, CureHealth);
CreateCustomAccessableConcept(CureHealth, CureHealth);
CreateGetTypeTemplateAccessableConcept(CureHealth, CureHealth);
#else
template <typename T>
concept CureHealthAccessable = requires(T x) {
    x.cureHealth;
    std::is_same_v<decltype(T::cureHealth), CureHealth>;
};

template <typename T>
concept GetCureHealthAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getCureHealth() } -> std::same_as<CureHealth&>;
    { std::as_const(x).getCureHealth() } -> std::same_as<const CureHealth&>;
};

#endif

}  // namespace traits
