#pragma once
#include "Usage/Types/Health/HealthConcepts.hpp"

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(Health, hp, Health);
#else
struct accessHealth {
    static constexpr auto& get(HealthAccessable auto& el) noexcept {
        return el.hp;
    }

    template <GetHealthAccessable T>
        requires(not(CustomHealthAccessable<T> or GetTypeTemplateHealthAccessable<T>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getHealth();
    }

    template <CustomHealthAccessable T>
        requires(not GetTypeTemplateHealthAccessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessHealth<std::remove_cvref_t<T>>::get(el);
    }

    template <GetTypeTemplateHealthAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<Health>();
    }
};
#endif

}  // namespace traits
