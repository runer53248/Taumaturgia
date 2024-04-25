#pragma once

class Name;

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateMemberAccessableConcept_convertible(Name, name, std::string);
CreateGetAccessableConcept_convertible(Name, std::string);
CreateCustomAccessableConcept_convertible(Name, std::string);
CreateUserTypeAccessableConcept_convertible(Name, Name, std::string);
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
concept CustomNameAccessable = requires(std::remove_cvref_t<T> x) {
    { CustomAccessName<T>::get(x) } -> std::convertible_to<std::string>;
    { CustomAccessName<T>::get(std::as_const(x)) } -> std::convertible_to<const std::string>;
};

template <typename T>
concept UserTypeNameAccessable = requires(std::remove_cvref_t<T> x) {
    { x.template getType<Name>() } -> std::convertible_to<std::string>;
    { std::as_const(x).template getType<Name>() } -> std::convertible_to<const std::string>;
};
#endif

}  // namespace traits
