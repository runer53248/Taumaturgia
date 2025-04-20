#pragma once
#include "Taumaturgia/Object/Enums/ActionStatus.hpp"
#include "Usage/Traits.hpp"

inline constexpr ActionStatus default_restore_behavior(Restoringable auto& obj, auto* target) {
    auto is_success = getOpt<Properties::Health>(*target).and_then([&](auto&& ref_wrap) -> std::optional<ActionStatus> {
        /*Health*/ auto& hp_ref = ref_wrap.get();

        if (auto& target_effects = hp_ref.effects(); not target_effects.empty()) {
            for (const auto& restoreEffect : trait<EffectTypeContainer>::get(obj)) {
                target_effects.removeEffectType(restoreEffect);
            }
        }
        return ActionStatus::Success;
    });
    return is_success.value_or(ActionStatus::Fail);
}
