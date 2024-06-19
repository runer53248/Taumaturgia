#pragma once
#include "Taumaturgia/Object/Object.hpp"

inline constexpr ActionStatus default_restore_behavior(Restoringable auto& obj, Object* target) {
    auto is_success = getOpt<Properties::Health>(*target).and_then([&](auto&& ref_wrap) {
        Health& hp_ref = ref_wrap;

        if (auto& target_effects = hp_ref.effects(); not target_effects.empty()) {
            for (const auto& restoreEffect : Restoringable_trait::get(obj)) {
                target_effects.removeEffectType(restoreEffect);
            }
        }
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
