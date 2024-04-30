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
    static constexpr auto& get(NameAccessable auto& el) noexcept {
        return el.name;
    }

    template <GetNameAccessable T>
        requires(not(CustomNameAccessable<T> or UserTypeNameAccessable<T>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getName();
    }

    template <CustomNameAccessable T>
        requires(not UserTypeNameAccessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessName<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeNameAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<Name>();
    }
};
#endif

}  // namespace traits

using Namingable_trait = traits::accessName;

template <typename T>
concept Namingable = trait_access_covertable<T, Namingable_trait, std::string>;
