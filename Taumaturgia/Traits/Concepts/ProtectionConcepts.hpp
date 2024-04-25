#pragma once

class Protection;

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateMemberAccessableConcept(Protection, protection, Protection);
CreateGetAccessableConcept(Protection, Protection);
CreateCustomAccessableConcept(Protection, Protection);
CreateUserTypeAccessableConcept(Protection, Protection);
#else
template <typename T>
concept ProtectionAccessable = requires(T x) {
    x.protection;
    std::is_same_v<decltype(T::protection), Protection>;
};

template <typename T>
concept GetProtectionAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getProtection() } -> same_as_ref<Protection>;
    { std::as_const(x).getProtection() } -> same_as_ref<const Protection>;
};

template <typename T>
struct CustomAccessProtection;

template <typename T>
concept CustomProtectionAccessable = requires(std::remove_cvref_t<T> x) {
    { CustomAccessProtection<T>::get(x) } -> same_as_ref<Protection>;
    { CustomAccessProtection<T>::get(std::as_const(x)) } -> same_as_ref<const Protection>;
};

template <typename T>
concept UserTypeProtectionAccessable = requires(std::remove_cvref_t<T> x) {
    { x.template getType<Protection>() } -> same_as_ref<Protection>;
    { std::as_const(x).template getType<Protection>() } -> same_as_ref<const Protection>;
};
#endif

}  // namespace traits
