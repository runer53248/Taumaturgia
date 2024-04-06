#pragma once
#include "Taumaturgia/Enums/ActionStatus.hpp"
#include "Taumaturgia/Object/Object.hpp"

inline ActionStatus default_heal_behavior(Healingable auto& obj, Object* target) {
    auto is_success = getOpt<Parameter::Health>(*target).and_then([&](auto&& ref_wrap) {
        Health& target_hp = ref_wrap;
        traits::accessCureHealth::get(obj).apply(target_hp);
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

#ifndef NO_PREMADE_STRATEGIES
ActionStatus HealStrategy_<Default>::operator()(Healingable auto& obj, Object* owner, Object* target) const {
    auto* suspect = Whom(owner, target);
    return default_heal_behavior(obj, suspect);
}
#else
ActionStatus UserStrategy_<CureHealth, Default>::operator()(Healingable auto& obj, Object* owner, Object* target) const {
    auto* suspect = Whom(owner, target);
    return default_heal_behavior(obj, suspect);
}
#endif
