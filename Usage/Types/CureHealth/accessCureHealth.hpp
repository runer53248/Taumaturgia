#pragma once
#include "Taumaturgia/Traits/trait.hpp"
#include "Usage/Types/CureHealth/CureHealthConcepts.hpp"

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(CureHealth, cureHealth, CureHealth);
#else
struct accessCureHealth : public impl::accessType<CureHealth> {
    template <typename T>
    static const bool accessable = helpers::trait_accessable<T, accessCureHealth, CureHealth>;

    template <CureHealthAccessable T>
        requires(not accessType<CureHealth>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.cureHealth);
    }

    template <GetCureHealthAccessable T>
        requires(not accessType<CureHealth>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getCureHealth();
    }

    using accessType<CureHealth>::get;
};
#endif

}  // namespace traits

template <>
struct trait_<CureHealth> {
    using type = traits::accessCureHealth;
};
