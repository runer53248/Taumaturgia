#pragma once
#include "../Helpers/traits_helper.hpp"

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
    { x.getCureHealth() } -> same_as_ref<CureHealth>;
    { std::as_const(x).getCureHealth() } -> same_as_ref<const CureHealth>;
};

template <typename T>
struct CustomAccessCureHealth;

template <typename T>
concept CustomCureHealthAccessable = requires(std::remove_cvref_t<T> x) {
    { CustomAccessCureHealth<T>::get(x) } -> same_as_ref<CureHealth>;
    { CustomAccessCureHealth<T>::get(std::as_const(x)) } -> same_as_ref<const CureHealth>;
};

template <typename T>
concept GetTypeTemplateCureHealthAccessable = requires(std::remove_cvref_t<T> x) {
    { x.template getType<CureHealth>() } -> same_as_ref<CureHealth>;
    { std::as_const(x).template getType<CureHealth>() } -> same_as_ref<const CureHealth>;
};
#endif

}  // namespace traits
