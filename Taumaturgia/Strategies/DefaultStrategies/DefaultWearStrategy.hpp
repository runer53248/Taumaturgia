#pragma once
#include "Taumaturgia/Object/Object.hpp"

inline constexpr ActionStatus default_wear_behavior(Wearingable auto& obj, Object* target) {
    auto result = getOpt<Properties::Wear>(*target).and_then([&](auto&& ref_wrap) {
        WearContainer& target_wear = ref_wrap;
        auto& armorWear = Wearingable_trait::get(obj);
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

template <>
#ifdef NO_PREMADE_STRATEGIES
struct UserStrategy_<WearContainer, Default, ActionStatus> {
#else
struct WearStrategy_<Default> {
#endif
    constexpr ActionStatus operator()(Wearingable auto& obj, Object* owner, Object* target) const {
        auto* suspect = Whom(owner, target);
        return default_wear_behavior(obj, suspect);
    }
};
