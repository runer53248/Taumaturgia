#pragma once
#include "Taumaturgia/Object/Enums/ActionStatus.hpp"
#include "Usage/Traits.hpp"

inline constexpr ActionStatus default_heal_behavior(Healingable auto& obj, auto* target) {
    auto is_success = getOpt<Properties::Health>(*target).and_then([&](auto&& ref_wrap) -> std::optional<ActionStatus> {
        /*Health*/ auto& target_hp = ref_wrap.get();
        trait<CureHealth>::get(obj).applyOn(target_hp);
        return ActionStatus::Success;
    });
    return is_success.value_or(ActionStatus::Fail);
}
