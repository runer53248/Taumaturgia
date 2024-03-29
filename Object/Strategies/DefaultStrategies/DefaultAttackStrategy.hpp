#pragma once

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
                WearContainer& target_wear = opt_wear.value();
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
