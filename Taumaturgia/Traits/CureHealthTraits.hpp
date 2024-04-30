#pragma once
#include "Helpers/traits_helper.hpp"
#include "Concepts/CureHealthConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

#ifdef WITH_ADD_PROPERTIES

#include "UserTypeTraits.hpp"
template <typename T>
concept Healingable = accessType_trait_able<T, CureHealth>;

using Healingable_trait = traits::accessType<CureHealth>;

#else

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(CureHealth, cureHealth, CureHealth);
#else
struct accessCureHealth {
    static auto& get(CureHealthAccessable auto& el) noexcept{
        return el.cureHealth;
    }

    template <GetCureHealthAccessable T>
        requires(not(CustomCureHealthAccessable<T> or UserTypeCureHealthAccessable<T>))
    static decltype(auto) get(T& el) noexcept {
        return el.getCureHealth();
    }

    template <CustomCureHealthAccessable T>
        requires(not UserTypeCureHealthAccessable<T>)
    static decltype(auto) get(T& el) noexcept{
        return CustomAccessCureHealth<std::remove_cvref_t<T>>::get(el);
    }

    template <UserTypeCureHealthAccessable T>
    static decltype(auto) get(T& el) noexcept {
        return el.template getType<CureHealth>();
    }
};
#endif

}  // namespace traits

template <typename T>
concept Healingable = trait_accessable<T, traits::accessCureHealth, CureHealth>;

using Healingable_trait = traits::accessCureHealth;

#endif
