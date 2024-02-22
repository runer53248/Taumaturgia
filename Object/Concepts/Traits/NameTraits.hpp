#pragma once
#include <string>
#include <type_traits>
#include <utility>  // for as_const
#include "helper/traits_helper.hpp"

struct Name;

namespace traits {

CreateAccessableConcept_convertible(Name, name, std::string);
CreateGetAccessableConcept_convertible(Name, std::string);
CreateCustomAccessableConcept_convertible(Name, std::string);
// CreateUserTypeAccessableConcept_convertible(Name, std::string);

template <typename T>
concept UserTypeNameAccessable = requires(std::remove_cvref_t<T> x) {
    { x.template getType<Name>() } -> std::convertible_to<std::string>;
    { std::as_const(x).template getType<Name>() } -> std::convertible_to<const std::string>;
};

struct accessName {
    static auto& get(NameAccessable auto& el) {
        return el.name;
    }

    template <GetNameAccessable T>
        requires(not(CustomNameAccessable<T> or UserTypeNameAccessable<T>))
    static decltype(auto) get(T& el) {
        return el.getName();
    }

    template <CustomNameAccessable T>
        requires(not UserTypeNameAccessable<T>)
    static decltype(auto) get(T& el) {
        return CustomAccessName<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeNameAccessable T>
    static decltype(auto) get(T& el) {
        return el.template getType<Name>();
    }
};

}  // namespace traits
