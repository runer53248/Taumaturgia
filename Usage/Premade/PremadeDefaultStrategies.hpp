#pragma once

template <>
struct AliveStrategy_<Default> {
    constexpr std::optional<AliveStatus> operator()(Livingable auto& obj) const {
        return default_alive_behavior(obj);
    }
};

template <>
struct AttackStrategy_<Default> {
    constexpr ActionStatus operator()(Damagingable auto& obj, Object* owner, Object* target) const {
        auto* suspect = Whom(owner, target);
        return default_attack_behavior(obj, suspect);
    }
};

template <>
struct DefendStrategy_<Default> {
    constexpr ActionStatus operator()(Protectingable auto& obj, Object* owner, Object* target) const {
        auto* suspect = Whom(owner, target);
        return default_defend_behavior(obj, suspect);
    }
};

template <>
struct HealStrategy_<Default> {
    constexpr ActionStatus operator()(Healingable auto& obj, Object* owner, Object* target) const {
        auto* suspect = Whom(owner, target);
        return default_heal_behavior(obj, suspect);
    }
};

template <>
struct RestoreStrategy_<Default> {
    constexpr ActionStatus operator()(Restoringable auto& obj, Object* owner, Object* target) const {
        auto* suspect = Whom(owner, target);
        return default_restore_behavior(obj, suspect);
    }
};

template <>
struct WearStrategy_<Default> {
    constexpr ActionStatus operator()(Wearingable auto& obj, Object* owner, Object* target) const {
        auto* suspect = Whom(owner, target);
        return default_wear_behavior(obj, suspect);
    }
};
