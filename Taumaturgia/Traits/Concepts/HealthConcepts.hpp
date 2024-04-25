#pragma once

class Health;

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateMemberAccessableConcept(Health, hp, Health);
CreateGetAccessableConcept(Health, Health);
CreateCustomAccessableConcept(Health, Health);
CreateUserTypeAccessableConcept(Health, Health);
#else
template <typename T>
concept HealthAccessable = requires(T x) {
    x.hp;
    std::is_same_v<decltype(T::hp), Health>;
};

template <typename T>
concept GetHealthAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getHealth() } -> same_as_ref<Health>;
    { std::as_const(x).getHealth() } -> same_as_ref<const Health>;
};

template <typename T>
struct CustomAccessHealth;

template <typename T>
concept CustomHealthAccessable = requires(std::remove_cvref_t<T> x) {
    { CustomAccessHealth<T>::get(x) } -> same_as_ref<Health>;
    { CustomAccessHealth<T>::get(std::as_const(x)) } -> same_as_ref<const Health>;
};

template <typename T>
concept UserTypeHealthAccessable = requires(std::remove_cvref_t<T> x) {
    { x.template getType<Health>() } -> same_as_ref<Health>;
    { std::as_const(x).template getType<Health>() } -> same_as_ref<const Health>;
};
#endif

}  // namespace traits
