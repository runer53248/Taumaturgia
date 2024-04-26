#pragma once
#include <string>
#include "Helpers/traits_helper.hpp"
#include "Concepts/NameConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

namespace traits {

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

template <typename T>
concept Namingable = trait_access_covertable<T, traits::accessName, std::string>;
