#pragma once
#include "Taumaturgia/Traits/Helpers/traits_helper.hpp"

class Protection;

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateMemberAccessableConcept(Protection, protection, Protection);
CreateGetAccessableConcept(Protection, Protection);
CreateCustomAccessableConcept(Protection, Protection);
CreateGetTypeTemplateAccessableConcept(Protection, Protection);
#else
template <typename T>
concept ProtectionAccessable = requires(T x) {
    x.protection;
    std::is_same_v<decltype(T::protection), Protection>;
};

template <typename T>
concept GetProtectionAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getProtection() } -> std::same_as<Protection&>;
    { std::as_const(x).getProtection() } -> std::same_as<const Protection&>;
};

#endif

}  // namespace traits
