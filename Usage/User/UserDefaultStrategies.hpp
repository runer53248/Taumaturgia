#pragma once

template <>
struct UserStrategy_<Health, Default> {
    static constexpr std::optional<AliveStatus> operator()(Livingable auto& obj) {
        return default_alive_behavior(obj);
    }
};

template <>
struct UserStrategy_<Damage, Default> {
    static constexpr ActionStatus operator()(Damagingable auto& obj, Object* owner, Object* target) {
        auto* suspect = Whom(owner, target);
        return default_attack_behavior(obj, suspect);
    }
};

template <>
struct UserStrategy_<Protection, Default> {
    static constexpr ActionStatus operator()(Protectingable auto& obj, Object* owner, Object* target) {
        auto* suspect = Whom(owner, target);
        return default_defend_behavior(obj, suspect);
    }
};

template <>
struct UserStrategy_<CureHealth, Default> {
    static constexpr ActionStatus operator()(Healingable auto& obj, Object* owner, Object* target) {
        auto* suspect = Whom(owner, target);
        return default_heal_behavior(obj, suspect);
    }
};

template <>
struct UserStrategy_<EffectTypeContainer, Default> {
    static constexpr ActionStatus operator()(Restoringable auto& obj, Object* owner, Object* target) {
        auto* suspect = Whom(owner, target);
        return default_restore_behavior(obj, suspect);
    }
};

template <>
struct UserStrategy_<WearContainer, Default> {
    static constexpr ActionStatus operator()(Wearingable auto& obj, Object* owner, Object* target) {
        auto* suspect = Whom(owner, target);
        return default_wear_behavior(obj, suspect);
    }
};
