#pragma once
#include "Object.hpp"
#include "StrategyHelpers.hpp"

std::optional<AliveStatus> AliveStrategy_<Default>::operator()(Livingable auto& obj) const {
    auto hp = traits::accessHealth::get(obj).value();
    if (hp > 0) {
        return AliveStatus::Healthy;
    } else if (hp == 0) {
        return AliveStatus::Dying;
    }
    return AliveStatus::Death;
}

ActionStatus AttackStrategy_<Default>::operator()(Damagingable auto& obj, Object* owner, Object* target) const {
    auto* suspect = Whom(owner, target);
    auto opt_protection = getOpt<Parameter::Protection>(*suspect);
    auto opt_restore = getOpt<Parameter::Restore>(*suspect);

    auto opt_alive_status = suspect->alive();
    if (opt_alive_status) {
        if (opt_alive_status.value() == AliveStatus::Death) {
            return ActionStatus::Fail;  // can't damage death target
        }
    } else {
        return ActionStatus::Fail;  // can't damage suspect
    }

    auto is_success = getOpt<Parameter::Health>(*suspect).and_then([&](auto&& ref_wrap) {
        Health& suspect_hp_ref = ref_wrap;

        if (suspect_hp_ref.value() <= -100) {
            return std::optional{ActionStatus::Interrupted};  // can't do more damage to target
        }

        suspect_hp_ref.removeHealth(traits::accessDamage::get(obj).value());

        if (auto attackEffect = traits::accessDamage::get(obj).effect(); attackEffect != EffectType::None) {  // attack have effect
            if (opt_protection.has_value()) {                                                                 // suspect have protection from effects
                Protection& suspect_protection = opt_protection.value();
                if (suspect_protection.protectEffects().contains(attackEffect.effectType())) {  // check protection against attack effect
                    return std::optional{ActionStatus::Partial_Success};
                }
            }

            suspect_hp_ref.effects().addEffectType(attackEffect);

            if (opt_restore.has_value()) {  // suspect can restore from effects
                EffectTypeContainer& suspect_restore = opt_restore.value();
                if (suspect_restore.contains(attackEffect.effectType())) {  // check suspect Restore to remove attack effect
                    suspect_hp_ref.effects().removeEffectType(attackEffect.effectType());
                    return std::optional{ActionStatus::Partial_Success};
                }
            }
        }
        return std::optional{ActionStatus::Success};
    });

    return is_success.value_or(ActionStatus::Fail);
}

ActionStatus DefendStrategy_<Default>::operator()(Protectingable auto& obj, Object* owner, Object* target) const {
    auto* suspect = Whom(owner, target);
    auto is_success = getOpt<Parameter::Wear>(*suspect).and_then([&](auto&& ref_wrap) {
        ProtectionContainer& suspect_protection = ref_wrap;
        suspect_protection.wearProtection(traits::accessProtection::get(obj));
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
    auto is_success = getOpt<Parameter::Health>(*suspect).and_then([&](auto&& ref_wrap) {
        Health& suspect_hp = ref_wrap;
        suspect_hp.addHealth(traits::accessCureHealth::get(obj).value());
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
    auto is_success = getOpt<Parameter::Health>(*suspect).and_then([&](auto&& ref_wrap) {
        Health& hp_ref = ref_wrap;

        if (auto& suspect_effects = hp_ref.effects(); not suspect_effects.empty()) {
            for (const auto& restoreEffect : traits::accessRestoreEffects::get(obj)) {
                suspect_effects.removeEffectType(restoreEffect);
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
