#pragma once
#include "Taumaturgia/Object/Enums/ActionStatus.hpp"
#include "Usage/Traits.hpp"

inline constexpr ActionStatus default_wear_behavior(Wearingable auto& obj, auto* target) {
    auto result = getOpt<Properties::Wear>(*target).and_then([&](auto&& ref_wrap) -> std::optional<ActionStatus> {
        /*WearContainer*/ auto& target_wear = ref_wrap.get();
        auto& armorWear = trait<WearContainer>::get(obj);
        auto locations = armorWear.getWearedLocations();
        if (locations.empty()) {
            return ActionStatus::Interrupted;
        }
        for (auto location : locations) {
            auto opt_protection = armorWear.armorAtLocation(location);
            if (opt_protection.has_value()) {
                target_wear.wearProtection(opt_protection.value());
            }
        }
        return ActionStatus::Success;
    });

    return result.value_or(ActionStatus::Fail);
}
