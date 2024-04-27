#pragma once
#include "Helpers/traits_helper.hpp"
#include "Concepts/CureHealthConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(CureHealth, cureHealth, CureHealth);
#else
struct accessCureHealth {
    static constexpr auto& get(CureHealthAccessable auto& el) noexcept{
        return el.cureHealth;
    }

    template <GetCureHealthAccessable T>
        requires(not(CustomCureHealthAccessable<T> or UserTypeCureHealthAccessable<T>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getCureHealth();
    }

    template <CustomCureHealthAccessable T>
        requires(not UserTypeCureHealthAccessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept{
        return CustomAccessCureHealth<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeCureHealthAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<CureHealth>();
    }
};
#endif

}  // namespace traits

template <typename T>
concept Healingable = trait_accessable<T, traits::accessCureHealth, CureHealth>;
