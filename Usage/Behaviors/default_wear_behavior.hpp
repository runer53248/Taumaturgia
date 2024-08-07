#pragma once
#include "Taumaturgia/Object/Object.hpp"

inline constexpr ActionStatus default_wear_behavior(Wearingable auto& obj, Object* target) {
    auto result = getOpt<Properties::Wear>(*target).and_then([&](auto&& ref_wrap) {
        WearContainer& target_wear = ref_wrap;
        auto& armorWear = trait<WearContainer>::get(obj);
        auto locations = armorWear.getWearedLocations();
        if (locations.empty()) {
            return std::optional{ActionStatus::Interrupted};
        }
        for (auto location : locations) {
            auto opt_protection = armorWear.armorAtLocation(location);
            if (opt_protection.has_value()) {
                target_wear.wearProtection(opt_protection.value());
            }
        }
        return std::optional{ActionStatus::Success};
    });

    return result.value_or(ActionStatus::Fail);
}
