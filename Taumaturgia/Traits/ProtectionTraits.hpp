#pragma once
#include "Helpers/traits_helper.hpp"
#include "Concepts/ProtectionConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(Protection, protection, Protection);
#else
struct accessProtection {
    static auto& get(ProtectionAccessable auto& el) noexcept{
        return el.protection;
    }

    template <GetProtectionAccessable T>
        requires(not(CustomProtectionAccessable<T> or UserTypeProtectionAccessable<T>))
    static decltype(auto) get(T& el) noexcept {
        return el.getProtection();
    }

    template <CustomProtectionAccessable T>
        requires(not UserTypeProtectionAccessable<T>)
    static decltype(auto) get(T& el) noexcept {
        return CustomAccessProtection<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeProtectionAccessable T>
    static decltype(auto) get(T& el) noexcept{
        return el.template getType<Protection>();
    }
};
#endif

}  // namespace traits

template <typename T>
concept Protectingable = trait_accessable<T, traits::accessProtection, Protection>;
