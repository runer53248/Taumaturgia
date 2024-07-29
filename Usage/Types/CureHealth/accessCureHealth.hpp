#pragma once
#include "Taumaturgia/Traits/accessType.hpp"
#include "Usage/Types/CureHealth/CureHealthConcepts.hpp"

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(CureHealth, cureHealth, CureHealth);
#else
struct accessCureHealth : public accessType<CureHealth> {
    template <typename T>
    static const bool accessable = helpers::trait_accessable<T, accessCureHealth, CureHealth>;

    static constexpr auto& get(CureHealthAccessable auto& el) noexcept {
        return el.cureHealth;
    }

    template <GetCureHealthAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getCureHealth();
    }

    using accessType<CureHealth>::get;
};
#endif

}  // namespace traits
