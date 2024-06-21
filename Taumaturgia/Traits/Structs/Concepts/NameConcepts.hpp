#pragma once
#include <string>
#include "Taumaturgia/Traits/Helpers/traits_helper.hpp"

class Name;

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateMemberAccessableConcept_convertible(Name, name, std::string);
CreateGetAccessableConcept_convertible(Name, std::string);
CreateCustomAccessableConcept_convertible(Name, std::string);
CreateGetTypeTemplateAccessableConcept(Name, Name, std::string);
#else
template <typename T>
concept NameAccessable = requires(T x) {
    x.name;
    requires std::is_convertible_v<decltype(T::name), std::string>;
};

template <typename T>
concept GetNameAccessable = requires(std::remove_cvref_t<T> x) {
    { x.getName() } -> std::convertible_to<std::string>;
    { std::as_const(x).getName() } -> std::convertible_to<const std::string>;
};

template <typename T>
struct CustomAccessName;

template <typename T>
concept CustomNameAccessable = helpers::custom_trait_convertible<T, CustomAccessName, std::string>;

template <typename T>
concept GetTypeTemplateNameAccessable = helpers::get_type_template_convertible<T, Name, std::string>;
#endif

}  // namespace traits
