#pragma once
#include "Taumaturgia/Traits/Concepts/ProtectionConcepts.hpp"

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(Protection, protection, Protection);
#else
struct accessProtection {
    static constexpr auto& get(ProtectionAccessable auto& el) noexcept {
        return el.protection;
    }

    template <GetProtectionAccessable T>
        requires(not(CustomProtectionAccessable<T> or GetTypeTemplateProtectionAccessable<T>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getProtection();
    }

    template <CustomProtectionAccessable T>
        requires(not GetTypeTemplateProtectionAccessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessProtection<std::remove_cvref_t<T> >::get(el);
    }

    template <GetTypeTemplateProtectionAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<Protection>();
    }
};
#endif

}  // namespace traits
