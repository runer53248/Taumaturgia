#pragma once
#include "Taumaturgia/Object/Object.hpp"

inline constexpr ActionStatus default_defend_behavior(Protectingable auto& obj, Object* target) {
    auto is_success = getOpt<Properties::Wear>(*target).and_then([&](auto&& ref_wrap) {
        WearContainer& target_protection = ref_wrap;
        target_protection.wearProtection(trait<Protection>::get(obj));
        return std::optional{true};
    });

    if (is_success.has_value()) {
        if (is_success.value()) {
            return ActionStatus::Success;
        }
        return ActionStatus::Interrupted;
    }
    return ActionStatus::Fail;
}
