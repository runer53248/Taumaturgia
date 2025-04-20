#pragma once
#include "Taumaturgia/Object/Enums/ActionStatus.hpp"
#include "Usage/Traits.hpp"

inline constexpr ActionStatus default_defend_behavior(Protectingable auto& obj, auto* target) {
    auto is_success = getOpt<Properties::Wear>(*target).and_then([&](auto&& ref_wrap) -> std::optional<ActionStatus> {
        /*WearContainer*/ auto& target_protection = ref_wrap.get();
        target_protection.wearProtection(trait<Protection>::get(obj));
        return ActionStatus::Success;
    });
    return is_success.value_or(ActionStatus::Fail);
}
