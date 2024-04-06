#pragma once

inline ActionStatus default_defend_behavior(Protectingable auto& obj, Object* target) {
    auto is_success = getOpt<Parameter::Wear>(*target).and_then([&](auto&& ref_wrap) {
        WearContainer& target_protection = ref_wrap;
        target_protection.wearProtection(traits::accessProtection::get(obj));
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
ActionStatus DefendStrategy_<Default>::operator()(Protectingable auto& obj, Object* owner, Object* target) const {
    auto* suspect = Whom(owner, target);
    return default_defend_behavior(obj, suspect);
}
#else
ActionStatus UserStrategy_<Protection, Default>::operator()(Protectingable auto& obj, Object* owner, Object* target) const {
    auto* suspect = Whom(owner, target);
    return default_defend_behavior(obj, suspect);
}
#endif
