#pragma once
#include "Object.hpp"

inline Object* Whom(Object *const owner, Object *const target) {
    if ((owner == target) or not target) {
        return owner;
    }
    return target;
}

std::optional<bool> AliveStrategy_<Default>::operator()(Livingable auto &obj) const {
    return obj.hp.value() > 0;
}

bool AttackStrategy_<Default>::operator()(Damagingable auto &obj, Object *owner, Object *target) const {
    if (not owner) {
        return false;
    }
    auto *suspect = Whom(owner, target);
    auto opt_ac = getOpt<Parameter::Ac>(*suspect);
    auto is_success = getOpt<Parameter::Hp>(*suspect)
        .and_then([&](auto&& ref_wrap) {
            Hp& suspect_hp_ref = ref_wrap;
            
            suspect_hp_ref.value() -= obj.dmg.value();

            if (obj.dmg.effect() != EffectType::None) {
                if (opt_ac.has_value()) {
                    AC& suspect_ac = opt_ac.value();
                    if (suspect_ac.protectEffects().contains(obj.dmg.effect().effectType())) {
                        return std::optional{true};
                    }
                }
                suspect_hp_ref.effects().addEffectType(obj.dmg.effect());
            }
            return std::optional{true};
        });
    return is_success.has_value();
}

bool DefendStrategy_<Default>::operator()(Protectingable auto &obj, Object *owner, Object *target) const {
    if (not owner) {
        return false;
    }
    auto *suspect = Whom(owner, target);
    auto is_success = getOpt<Parameter::Ac>(*suspect)
        .and_then([&](auto&& ref_wrap) {
            AC& suspect_ac = ref_wrap;
            suspect_ac.value(obj.ac.location()) = obj.ac.value();
            suspect_ac.protectEffects().addEffectTypes(obj.ac.protectEffects()); //TODO: replacing ac location should change its protecton effects
            return std::optional{true};
        });
    return is_success.has_value();
}

bool HealStrategy_<Default>::operator()(Healingable auto &obj, Object *owner, Object *target) const {
    if (not owner) {
        return false;
    }
    auto *suspect = Whom(owner, target);
    auto is_success = getOpt<Parameter::Hp>(*suspect)
        .and_then([&](auto&& ref_wrap) {
            Hp& suspect_hp = ref_wrap;
            suspect_hp.value() += obj.cureHp.value();
            return std::optional{true};
        });
    return is_success.has_value();
}

bool RestoreStrategy_<Default>::operator()(Restoringable auto &obj, Object *owner, Object *target) const {
    if (not owner) {
        return false;
    }
    auto *suspect = Whom(owner, target);
    auto is_success = getOpt<Parameter::Hp>(*suspect)
        .and_then([&](auto&& ref_wrap) {
            Hp& hp_ref = ref_wrap;

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
    if constexpr (P == Parameter::Hp) {
        if constexpr (Livingable<type>) {
            return result_type{std::ref(obj.hp)};
        }
    }
    if constexpr (P == Parameter::CureHp) {
        if constexpr (Healingable<type>) {
            return result_type{std::ref(obj.cureHp)};
        }
    }
    if constexpr (P == Parameter::Ac) {
        if constexpr (Protectingable<type>) {
            return result_type{std::ref(obj.ac)};
        }
    }
    if constexpr (P == Parameter::Damage) {
        if constexpr (Damagingable<type>) {
            return result_type{std::ref(obj.dmg)};
        }
    }
    if constexpr (P == Parameter::Restore) {
        if constexpr (Restoringable<type>) {
            return result_type{std::ref(obj.restoreEffects)};
        }
    }
    return result_type{};
}
