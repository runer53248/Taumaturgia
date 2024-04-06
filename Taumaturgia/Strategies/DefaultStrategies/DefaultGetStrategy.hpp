#pragma once
#include "Taumaturgia/Concepts/Types/Enums/Parameter.hpp"
#include "Taumaturgia/Strategies/GetStrategy.hpp"

template <Parameter PARAMETER>
inline auto default_get_behavior(Gettingable auto& obj) {
    using result_type = std::conditional_t<
        std::is_const_v<std::remove_reference_t<decltype(obj)>>,
        get_optional_variant_const_type,
        get_optional_variant_type>;

    using type = std::remove_reference_t<decltype(obj)>;
    if constexpr (PARAMETER == Parameter::Health) {
        if constexpr (Livingable<type>) {
            return result_type{
                std::ref(traits::accessHealth::get(obj))};
        }
    } else if constexpr (PARAMETER == Parameter::CureHealth) {
        if constexpr (Healingable<type>) {
            return result_type{
                std::ref(traits::accessCureHealth::get(obj))};
        }
    } else if constexpr (PARAMETER == Parameter::Protection) {
        if constexpr (Protectingable<type>) {
            return result_type{
                std::ref(traits::accessProtection::get(obj))};
        }
    } else if constexpr (PARAMETER == Parameter::Damage) {
        if constexpr (Damagingable<type>) {
            return result_type{
                std::ref(traits::accessDamage::get(obj))};
        }
    } else if constexpr (PARAMETER == Parameter::Restore) {
        if constexpr (Restoringable<type>) {
            return result_type{
                std::ref(traits::accessRestoreEffects::get(obj))};
        }
    } else if constexpr (PARAMETER == Parameter::Wear) {
        if constexpr (Wearingable<type>) {
            return result_type{
                std::ref(traits::accessArmorWear::get(obj))};
        }
    }
    return result_type{};
}

template <Parameter PARAMETER>
auto GetStrategy_<Default>::operator()(Gettingable auto& obj) const {
    return default_get_behavior<PARAMETER>(obj);
}
