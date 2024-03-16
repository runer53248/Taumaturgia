#pragma once
#include <string>
#include "helper/traits_helper.hpp"

struct Name;

namespace traits {

CreateAccessableConcept_convertible(Name, name, std::string);
CreateGetAccessableConcept_convertible(Name, std::string);
CreateCustomAccessableConcept_convertible(Name, std::string);
CreateUserTypeAccessableConcept_convertible(Name, Name, std::string);

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(Name, name, Name);
#else
struct accessName {
    static auto& get(NameAccessable auto& el) noexcept {
        return el.name;
    }

    template <GetNameAccessable T>
        requires(not(CustomNameAccessable<T> or UserTypeNameAccessable<T>))
    static decltype(auto) get(T& el) noexcept {
        return el.getName();
    }

    template <CustomNameAccessable T>
        requires(not UserTypeNameAccessable<T>)
    static decltype(auto) get(T& el) noexcept {
        return CustomAccessName<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeNameAccessable T>
    static decltype(auto) get(T& el) noexcept {
        return el.template getType<Name>();
    }
};
#endif

}  // namespace traits
