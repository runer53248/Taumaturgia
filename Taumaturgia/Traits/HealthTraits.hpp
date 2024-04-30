#pragma once
#include "Helpers/traits_helper.hpp"
#include "Concepts/HealthConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

#ifdef WITH_ADD_PROPERTIES

#include "UserTypeTraits.hpp"
template <typename T>
concept Livingable = accessType_trait_able<T, Health>;

using Livingable_trait = traits::accessType<Health>;

#else

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(Health, hp, Health);
#else
struct accessHealth {
    static constexpr auto& get(HealthAccessable auto& el) noexcept {
        return el.hp;
    }

    template <GetHealthAccessable T>
        requires(not(CustomHealthAccessable<T> or UserTypeHealthAccessable<T>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getHealth();
    }

    template <CustomHealthAccessable T>
        requires(not UserTypeHealthAccessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessHealth<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeHealthAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<Health>();
    }
};
#endif

}  // namespace traits

template <typename T>
concept Livingable = trait_accessable<T, traits::accessHealth, Health>;

using Livingable_trait = traits::accessHealth;

#endif
