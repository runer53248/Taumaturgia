#pragma once
#include "Taumaturgia/Types/Enums/Properties.hpp"
#include "Taumaturgia/Strategies/GetStrategy.hpp"

template <Properties PROPERTY>
inline auto default_get_behavior(Gettingable auto& obj) {
    using result_type = std::conditional_t<
        std::is_const_v<std::remove_reference_t<decltype(obj)>>,
        optional_get_variant_const_type,
        optional_get_variant_type>;

    using type = std::remove_reference_t<decltype(obj)>;
    if constexpr (PROPERTY == Properties::Health) {
        if constexpr (Livingable<type>) {
            return result_type{
                std::ref(Livingable_trait::get(obj))};
        }
    } else if constexpr (PROPERTY == Properties::CureHealth) {
        if constexpr (Healingable<type>) {
            return result_type{
                std::ref(Healingable_trait::get(obj))};
        }
    } else if constexpr (PROPERTY == Properties::Protection) {
        if constexpr (Protectingable<type>) {
            return result_type{
                std::ref(Protectingable_trait::get(obj))};
        }
    } else if constexpr (PROPERTY == Properties::Damage) {
        if constexpr (Damagingable<type>) {
            return result_type{
                std::ref(Damagingable_trait::get(obj))};
        }
    } else if constexpr (PROPERTY == Properties::Restore) {
        if constexpr (Restoringable<type>) {
            return result_type{
                std::ref(Restoringable_trait::get(obj))};
        }
    } else if constexpr (PROPERTY == Properties::Wear) {
        if constexpr (Wearingable<type>) {
            return result_type{
                std::ref(Wearingable_trait::get(obj))};
        }
    }
    return result_type{};
}

template <Properties PROPERTY>
auto GetStrategy_<Default>::operator()(Gettingable auto& obj) const {
    return default_get_behavior<PROPERTY>(obj);
}
