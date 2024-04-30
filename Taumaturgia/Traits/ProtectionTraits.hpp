#pragma once
#include "Helpers/traits_helper.hpp"
#include "Concepts/ProtectionConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

#ifdef WITH_ADD_PROPERTIES

#include "UserTypeTraits.hpp"
template <typename T>
concept Protectingable = accessType_trait_able<T, Protection>;

using Protectingable_trait = traits::accessType<Protection>;

#else

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(Protection, protection, Protection);
#else
struct accessProtection {
    static constexpr auto& get(ProtectionAccessable auto& el) noexcept{
        return el.protection;
    }

    template <GetProtectionAccessable T>
        requires(not(CustomProtectionAccessable<T> or UserTypeProtectionAccessable<T>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getProtection();
    }

    template <CustomProtectionAccessable T>
        requires(not UserTypeProtectionAccessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessProtection<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeProtectionAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept{
        return el.template getType<Protection>();
    }
};
#endif

}  // namespace traits

using Protectingable_trait = traits::accessProtection;

template <typename T>
concept Protectingable = trait_accessable<T, Protectingable_trait, Protection>;

#endif
