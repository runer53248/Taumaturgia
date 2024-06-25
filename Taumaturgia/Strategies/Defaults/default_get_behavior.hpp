#pragma once
#include "Taumaturgia/Strategies/GetStrategy.hpp"
#include "Taumaturgia/Types/Enums/Properties.hpp"

template <Properties PROPERTY>
inline constexpr auto default_get_behavior(Gettingable auto& obj) -> to_optional_get_variant<decltype(obj)> {
    using type = std::remove_reference_t<decltype(obj)>;

    if constexpr (PROPERTY == Properties::Health) {
        if constexpr (Livingable<type>) {
            return std::ref(Livingable_trait::get(obj));
        }
    } else if constexpr (PROPERTY == Properties::CureHealth) {
        if constexpr (Healingable<type>) {
            return std::ref(Healingable_trait::get(obj));
        }
    } else if constexpr (PROPERTY == Properties::Protection) {
        if constexpr (Protectingable<type>) {
            return std::ref(Protectingable_trait::get(obj));
        }
    } else if constexpr (PROPERTY == Properties::Damage) {
        if constexpr (Damagingable<type>) {
            return std::ref(Damagingable_trait::get(obj));
        }
    } else if constexpr (PROPERTY == Properties::Restore) {
        if constexpr (Restoringable<type>) {
            return std::ref(Restoringable_trait::get(obj));
        }
    } else if constexpr (PROPERTY == Properties::Wear) {
        if constexpr (Wearingable<type>) {
            return std::ref(Wearingable_trait::get(obj));
        }
    }
    return {};
}
