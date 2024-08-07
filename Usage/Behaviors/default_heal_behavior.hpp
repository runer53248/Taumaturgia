#pragma once
#include "Taumaturgia/Object/Object.hpp"

inline constexpr ActionStatus default_heal_behavior(Healingable auto& obj, Object* target) {
    auto is_success = getOpt<Properties::Health>(*target).and_then([&](auto&& ref_wrap) {
        Health& target_hp = ref_wrap;
        trait<CureHealth>::get(obj).applyOn(target_hp);
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
