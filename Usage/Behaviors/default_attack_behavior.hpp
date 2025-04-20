#pragma once
#include "Taumaturgia/Object/Enums/ActionStatus.hpp"
#include "Usage/Traits.hpp"

inline constexpr ActionStatus default_attack_behavior(Damagingable auto& obj, auto* target) {
    if (auto opt_alive_status = target->alive()) {
        if (opt_alive_status.value() == AliveStatus::Death) {
            return ActionStatus::Invalid;  // can't damage death target
        }
    } else {
        return ActionStatus::Invalid;  // can't damage non alive target
    }

    auto is_success = getOpt<Properties::Health>(*target).and_then([&](auto&& ref_wrap) -> std::optional<ActionStatus> {
        /*Health*/ auto& target_hp_ref = ref_wrap.get();

        if (target_hp_ref.value() <= -100) {
            return ActionStatus::Interrupted;  // can't do more damage to target
        }

        target_hp_ref.removeHealth(trait<Damage>::get(obj).value());

        if (const auto attackEffect = trait<Damage>::get(obj).effect(); attackEffect.effectType() != EffectType::None) {  // attack have effect
            auto opt_ref_protection = getOpt<Properties::Protection>(*target);
            if (opt_ref_protection.has_value()) {  // target have protection against effect
                /*Protection*/ auto& target_protection = opt_ref_protection.value().get();
                if (target_protection.protectEffects().contains(attackEffect.effectType())) {  // check protection against attack effect
                    return ActionStatus::Partial_Success;
                }
            }

            auto opt_ref_wear = getOpt<Properties::Wear>(*target);
            if (opt_ref_wear.has_value()) {  // target can have protection against effect from wearables
                /*WearContainer*/ auto& target_wear = opt_ref_wear.value().get();
                if (target_wear.protectEffects().contains(attackEffect.effectType())) {  // check wear protection against attack effect
                    return ActionStatus::Partial_Success;
                }
            }

            target_hp_ref.effects().addEffectType(attackEffect);

            auto opt_ref_restore = getOpt<Properties::Restore>(*target);
            if (opt_ref_restore.has_value()) {  // target can restore from effect
                /*EffectTypeContainer*/ auto& target_restore = opt_ref_restore.value().get();
                if (target_restore.contains(attackEffect.effectType())) {  // check target Restore to remove attack effect
                    target_hp_ref.effects().removeEffectType(attackEffect.effectType());
                    return ActionStatus::Partial_Success;
                }
            }
        }
        return ActionStatus::Success;
    });

    return is_success.value_or(ActionStatus::Fail);
}
