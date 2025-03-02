#pragma once
#include "Taumaturgia/Traits/trait.hpp"
#include "Usage/Types/Health/HealthConcepts.hpp"

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(Health, hp, Health);
#else
struct accessHealth : public accessType<Health> {
    template <typename T>
    static const bool accessable = helpers::trait_accessable<T, accessHealth, Health>;

    template <HealthAccessable T>
        requires(not accessType<Health>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.hp);
    }

    template <GetHealthAccessable T>
        requires(not accessType<Health>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getHealth();
    }

    using accessType<Health>::get;
};
#endif

}  // namespace traits

template <>
struct trait_<Health> {
    using type = traits::accessHealth;
};
