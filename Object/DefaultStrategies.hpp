#pragma once
#include "Object.hpp"

inline Object* Whom(Object *const owner, Object *const target) {
    if (not owner and not target) {
        throw std::logic_error("Whom function get nullptr as both object owner and target.");
    }

    if ((owner == target) or not target) {
        return owner;
    }
    return target;
}

std::optional<bool> AliveStrategy_<Default>::operator()(Livingable auto &obj) const {
    return obj.hp.value() > 0;
}

bool AttackStrategy_<Default>::operator()(Damagingable auto &obj, Object *owner, Object *target) const {
    auto *suspect = Whom(owner, target);
    auto opt_ac = getOpt<Parameter::Armor>(*suspect);
    auto opt_restore = getOpt<Parameter::Restore>(*suspect);

    auto is_success = getOpt<Parameter::Health>(*suspect).and_then([&](auto&& ref_wrap) {
        Health& suspect_hp_ref = ref_wrap;
        
        suspect_hp_ref.removeHealth(obj.dmg.value());

        if (auto attackEffect = obj.dmg.effect(); attackEffect != EffectType::None) {


            if (opt_ac.has_value()) {
                ArmorClass& suspect_ac = opt_ac.value();
                if (suspect_ac.protectEffects().contains(attackEffect.effectType())) { // check ArmorClass protection against attack effect
                    return std::optional{true};
                }
            }
            suspect_hp_ref.effects().addEffectType(attackEffect);

            if (opt_restore.has_value()) {
                EffectTypeContainer& suspect_restore = opt_restore.value();
                if (suspect_restore.contains(attackEffect.effectType())) { // check suspect Restore to remove attack effect
                    suspect_hp_ref.effects().removeEffectType(attackEffect.effectType());
                }
            }
        }
        return std::optional{true};
    });
    return is_success.has_value();
}

bool DefendStrategy_<Default>::operator()(Protectingable auto &obj, Object *owner, Object *target) const {
    auto *suspect = Whom(owner, target);
    auto is_success = getOpt<Parameter::Wear>(*suspect).and_then([&](auto&& ref_wrap) {
        ArmorClassContainer& suspect_ac = ref_wrap;
        suspect_ac.wearArmor(obj.ac);
        return std::optional{true};
    });
    
    return is_success.has_value();
}

bool HealStrategy_<Default>::operator()(Healingable auto &obj, Object *owner, Object *target) const {
    auto *suspect = Whom(owner, target);
    auto is_success = getOpt<Parameter::Health>(*suspect).and_then([&](auto&& ref_wrap) {
        Health& suspect_hp = ref_wrap;
        suspect_hp.addHealth(obj.cureHealth.value());
        return std::optional{true};
    });
    return is_success.has_value();
}

bool RestoreStrategy_<Default>::operator()(Restoringable auto &obj, Object *owner, Object *target) const {
    auto *suspect = Whom(owner, target);
    auto is_success = getOpt<Parameter::Health>(*suspect).and_then([&](auto&& ref_wrap) {
        Health& hp_ref = ref_wrap;

        if (auto& suspect_effects = hp_ref.effects(); not suspect_effects.empty()) {
            for (const auto& restoreEffect : obj.restoreEffects) {
                suspect_effects.removeEffectType(restoreEffect);
            }
        }
        return std::optional{true};
    });
    return is_success.has_value();
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
            return result_type{std::ref(obj.hp)};
        }
    } else if constexpr (P == Parameter::CureHealth) {
        if constexpr (Healingable<type>) {
            return result_type{std::ref(obj.cureHealth)};
        }
    } else if constexpr (P == Parameter::Armor) {
        if constexpr (Protectingable<type>) {
            return result_type{std::ref(obj.ac)};
        }
    } else if constexpr (P == Parameter::Damage) {
        if constexpr (Damagingable<type>) {
            return result_type{std::ref(obj.dmg)};
        }
    } else if constexpr (P == Parameter::Restore) {
        if constexpr (Restoringable<type>) {
            return result_type{std::ref(obj.restoreEffects)};
        }
    } else if constexpr (P == Parameter::Wear) {
        if constexpr (Wearingable<type>) {
            return result_type{std::ref(obj.armorWear)};
        }
    }
    return result_type{};
}
