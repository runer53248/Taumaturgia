#pragma once

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(CureHealth, cureHealth, CureHealth);
#else
struct accessCureHealth {
    static constexpr auto& get(CureHealthAccessable auto& el) noexcept {
        return el.cureHealth;
    }

    template <GetCureHealthAccessable T>
        requires(not(CustomCureHealthAccessable<T> or GetTypeTemplateCureHealthAccessable<T>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getCureHealth();
    }

    template <CustomCureHealthAccessable T>
        requires(not GetTypeTemplateCureHealthAccessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessCureHealth<std::remove_cvref_t<T> >::get(el);
    }

    template <GetTypeTemplateCureHealthAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<CureHealth>();
    }
};
#endif

}  // namespace traits
