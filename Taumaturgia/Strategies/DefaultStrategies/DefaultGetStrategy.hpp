#pragma once
#include "Taumaturgia/Types/Enums/Properties.hpp"
#include "Taumaturgia/Strategies/GetStrategy.hpp"

template <Properties PARAMETER>
inline auto default_get_behavior(Gettingable auto& obj) {
    using result_type = std::conditional_t<
        std::is_const_v<std::remove_reference_t<decltype(obj)>>,
        get_optional_variant_const_type,
        get_optional_variant_type>;

    using type = std::remove_reference_t<decltype(obj)>;
    if constexpr (PARAMETER == Properties::Health) {
        if constexpr (Livingable<type>) {
            return result_type{
                std::ref(traits::accessHealth::get(obj))};
        }
    } else if constexpr (PARAMETER == Properties::CureHealth) {
        if constexpr (Healingable<type>) {
            return result_type{
                std::ref(traits::accessCureHealth::get(obj))};
        }
    } else if constexpr (PARAMETER == Properties::Protection) {
        if constexpr (Protectingable<type>) {
            return result_type{
                std::ref(traits::accessProtection::get(obj))};
        }
    } else if constexpr (PARAMETER == Properties::Damage) {
        if constexpr (Damagingable<type>) {
            return result_type{
                std::ref(traits::accessDamage::get(obj))};
        }
    } else if constexpr (PARAMETER == Properties::Restore) {
        if constexpr (Restoringable<type>) {
            return result_type{
                std::ref(traits::accessRestoreEffects::get(obj))};
        }
    } else if constexpr (PARAMETER == Properties::Wear) {
        if constexpr (Wearingable<type>) {
            return result_type{
                std::ref(traits::accessArmorWear::get(obj))};
        }
    }
    return result_type{};
}

template <Properties PARAMETER>
auto GetStrategy_<Default>::operator()(Gettingable auto& obj) const {
    return default_get_behavior<PARAMETER>(obj);
}
