#pragma once
#include "Taumaturgia/Object/Object.hpp"

inline constexpr ActionStatus default_heal_behavior(Healingable auto& obj, Object* target) {
    auto is_success = getOpt<Properties::Health>(*target).and_then([&](auto&& ref_wrap) {
        Health& target_hp = ref_wrap;
        Healingable_trait::get(obj).applyOn(target_hp);
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
#ifndef NO_PREMADE_STRATEGIES
struct HealStrategy_<Default> {
#else
struct UserStrategy_<CureHealth, Default, ActionStatus> {
#endif
    constexpr ActionStatus operator()(Healingable auto& obj, Object* owner, Object* target) const {
        auto* suspect = Whom(owner, target);
        return default_heal_behavior(obj, suspect);
    }
};
