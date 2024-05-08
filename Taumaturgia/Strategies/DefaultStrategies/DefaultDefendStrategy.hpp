#pragma once
#include "Taumaturgia/Object/Object.hpp"

inline constexpr ActionStatus default_defend_behavior(Protectingable auto& obj, Object* target) {
    auto is_success = getOpt<Properties::Wear>(*target).and_then([&](auto&& ref_wrap) {
        WearContainer& target_protection = ref_wrap;
        target_protection.wearProtection(Protectingable_trait::get(obj));
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

template <>
#ifdef NO_PREMADE_STRATEGIES
struct UserStrategy_<Protection, Default, ActionStatus> {
#else
struct DefendStrategy_<Default> {
#endif
    constexpr ActionStatus operator()(Protectingable auto& obj, Object* owner, Object* target) const {
        auto* suspect = Whom(owner, target);
        return default_defend_behavior(obj, suspect);
    }
};
