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
    auto is_success = get(*suspect, Parameter::Hp)
        .and_then([&](auto&& variant) {
            Hp& value_ref = Get<Hp>(variant);
            value_ref.value() -= obj.dmg.value();
            return std::optional{true};
        });
    return is_success.has_value();
}

bool DefendStrategy_<Default>::operator()(Protectingable auto &obj, Object *owner, Object *target) const {
    if (not owner) {
        return false;
    }
    auto *suspect = Whom(owner, target);
    auto is_success = get(*suspect, Parameter::Ac)
        .and_then([&](auto&& variant) {
            AC& ac_ref = Get<AC>(variant);
            ac_ref.value(obj.ac.location()) = obj.ac.value();
            return std::optional{true};
        });
    return is_success.has_value();
}

bool HealStrategy_<Default>::operator()(Healingable auto &obj, Object *owner, Object *target) const {
    if (not owner) {
        return false;
    }
    auto *suspect = Whom(owner, target);
    auto is_success = get(*suspect, Parameter::Hp)
        .and_then([&](auto&& variant) {
            Hp& value_ref = Get<Hp>(variant);
            value_ref.value() += obj.cureHp.value();
            return std::optional{true};
        });
    return is_success.has_value();
}

template <Parameter P>
auto GetStrategy_<Default>::operator()(Gettingable auto &obj) const {
    using result_type = std::conditional_t<
		std::is_const_v<std::remove_reference_t<decltype(obj)>>,
		optional_get_const_result_type,
		optional_get_result_type>;

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
    return result_type{};
}
