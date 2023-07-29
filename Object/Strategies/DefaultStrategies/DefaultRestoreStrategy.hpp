#pragma once

inline ActionStatus default_restore_behavior(Restoringable auto& obj, Object* target) {
    auto is_success = getOpt<Parameter::Health>(*target).and_then([&](auto&& ref_wrap) {
        Health& hp_ref = ref_wrap;

        if (auto& target_effects = hp_ref.effects(); not target_effects.empty()) {
            for (const auto& restoreEffect : traits::accessRestoreEffects::get(obj)) {
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

ActionStatus RestoreStrategy_<Default>::operator()(Restoringable auto& obj, Object* owner, Object* target) const {
    auto* suspect = Whom(owner, target);
    return default_restore_behavior(obj, suspect);
}
