#pragma once
#include "Object.hpp"
#include "StrategyHelpers.hpp"

inline std::optional<AliveStatus> default_alive_behavior(Livingable auto& obj) {
    auto hp = traits::accessHealth::get(obj).value();
    if (hp > 0) {
        return AliveStatus::Healthy;
    } else if (hp == 0) {
        return AliveStatus::Dying;
    }
    return AliveStatus::Death;
}

std::optional<AliveStatus> AliveStrategy_<Default>::operator()(Livingable auto& obj) const {
    return default_alive_behavior(obj);
}

inline ActionStatus default_attack_behavior(Damagingable auto& obj, Object* target) {
    auto opt_protection = getOpt<Parameter::Protection>(*target);
    auto opt_wear = getOpt<Parameter::Wear>(*target);
    auto opt_restore = getOpt<Parameter::Restore>(*target);

    auto opt_alive_status = target->alive();
    if (opt_alive_status) {
        if (opt_alive_status.value() == AliveStatus::Death) {
            return ActionStatus::Invalid;  // can't damage death target
        }
    } else {
        return ActionStatus::Invalid;  // can't damage non alive target
    }

    auto is_success = getOpt<Parameter::Health>(*target).and_then([&](auto&& ref_wrap) {
        Health& target_hp_ref = ref_wrap;

        if (target_hp_ref.value() <= -100) {
            return std::optional{ActionStatus::Interrupted};  // can't do more damage to target
        }

        target_hp_ref.removeHealth(traits::accessDamage::get(obj).value());

        if (auto attackEffect = traits::accessDamage::get(obj).effect(); attackEffect != EffectType::None) {  // attack have effect

            if (opt_protection.has_value()) {  // target have protection against effect
                Protection& target_protection = opt_protection.value();
                if (target_protection.protectEffects().contains(attackEffect.effectType())) {  // check protection against attack effect
                    return std::optional{ActionStatus::Partial_Success};
                }
            }

            if (opt_wear.has_value()) {  // target can have protection against effect from wearables
                ProtectionContainer& target_wear = opt_wear.value();
                if (target_wear.protectEffects().contains(attackEffect.effectType())) {  // check wear protection against attack effect
                    return std::optional{ActionStatus::Partial_Success};
                }
            }

            target_hp_ref.effects().addEffectType(attackEffect);

            if (opt_restore.has_value()) {  // target can restore from effect
                EffectTypeContainer& target_restore = opt_restore.value();
                if (target_restore.contains(attackEffect.effectType())) {  // check target Restore to remove attack effect
                    target_hp_ref.effects().removeEffectType(attackEffect.effectType());
                    return std::optional{ActionStatus::Partial_Success};
                }
            }
        }
        return std::optional{ActionStatus::Success};
    });

    return is_success.value_or(ActionStatus::Fail);
}

ActionStatus AttackStrategy_<Default>::operator()(Damagingable auto& obj, Object* owner, Object* target) const {
    auto* suspect = Whom(owner, target);
    return default_attack_behavior(obj, suspect);
}

inline ActionStatus default_defend_behavior(Protectingable auto& obj, Object* target) {
    auto is_success = getOpt<Parameter::Wear>(*target).and_then([&](auto&& ref_wrap) {
        ProtectionContainer& target_protection = ref_wrap;
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

ActionStatus DefendStrategy_<Default>::operator()(Protectingable auto& obj, Object* owner, Object* target) const {
    auto* suspect = Whom(owner, target);
    return default_defend_behavior(obj, suspect);
}

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

template <Parameter P>
auto GetStrategy_<Default>::operator()(Gettingable auto& obj) const {
    using result_type = std::conditional_t<
        std::is_const_v<std::remove_reference_t<decltype(obj)>>,
        get_optional_variant_const_type,
        get_optional_variant_type>;

    using type = std::remove_reference_t<decltype(obj)>;
    if constexpr (P == Parameter::Health) {
        if constexpr (Livingable<type>) {
            return result_type{
                std::ref(traits::accessHealth::get(obj))};
        }
    } else if constexpr (P == Parameter::CureHealth) {
        if constexpr (Healingable<type>) {
            return result_type{
                std::ref(traits::accessCureHealth::get(obj))};
        }
    } else if constexpr (P == Parameter::Protection) {
        if constexpr (Protectingable<type>) {
            return result_type{
                std::ref(traits::accessProtection::get(obj))};
        }
    } else if constexpr (P == Parameter::Damage) {
        if constexpr (Damagingable<type>) {
            return result_type{
                std::ref(traits::accessDamage::get(obj))};
        }
    } else if constexpr (P == Parameter::Restore) {
        if constexpr (Restoringable<type>) {
            return result_type{
                std::ref(traits::accessRestoreEffects::get(obj))};
        }
    } else if constexpr (P == Parameter::Wear) {
        if constexpr (Wearingable<type>) {
            return result_type{
                std::ref(traits::accessArmorWear::get(obj))};
        }
    }
    return result_type{};
}
