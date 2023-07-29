#pragma once
#include "Object/Concepts/Types/Enums/Parameter.hpp"
#include "Object/Strategies/GetStrategy.hpp"

template <Parameter P>
auto GetStrategy_<Default>::operator()(Gettingable auto& obj) const {
    using result_type = std::conditional_t<
        std::is_const_v<std::remove_reference_t<decltype(obj)>>,
        get_optional_variant_const_type,
        get_optional_variant_type>;

    using type = std::remove_reference_t<decltype(obj)>;
    if constexpr (P == Parameter::Health) {
        if constexpr (Livingable<type>) {
            return result_type{
                std::ref(traits::accessHealth::get(obj))};
        }
    } else if constexpr (P == Parameter::CureHealth) {
        if constexpr (Healingable<type>) {
            return result_type{
                std::ref(traits::accessCureHealth::get(obj))};
        }
    } else if constexpr (P == Parameter::Protection) {
        if constexpr (Protectingable<type>) {
            return result_type{
                std::ref(traits::accessProtection::get(obj))};
        }
    } else if constexpr (P == Parameter::Damage) {
        if constexpr (Damagingable<type>) {
            return result_type{
                std::ref(traits::accessDamage::get(obj))};
        }
    } else if constexpr (P == Parameter::Restore) {
        if constexpr (Restoringable<type>) {
            return result_type{
                std::ref(traits::accessRestoreEffects::get(obj))};
        }
    } else if constexpr (P == Parameter::Wear) {
        if constexpr (Wearingable<type>) {
            return result_type{
                std::ref(traits::accessArmorWear::get(obj))};
        }
    }
    return result_type{};
}
