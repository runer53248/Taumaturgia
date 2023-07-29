#pragma once

inline ActionStatus default_heal_behavior(Healingable auto& obj, Object* target) {
    auto is_success = getOpt<Parameter::Health>(*target).and_then([&](auto&& ref_wrap) {
        Health& target_hp = ref_wrap;
        target_hp.addHealth(traits::accessCureHealth::get(obj).value());
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

ActionStatus HealStrategy_<Default>::operator()(Healingable auto& obj, Object* owner, Object* target) const {
    auto* suspect = Whom(owner, target);
    return default_heal_behavior(obj, suspect);
}
