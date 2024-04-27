#pragma once
#include <concepts>
#include "Taumaturgia/Traits/DamageTraits.hpp"
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"

template <typename T>
struct AttackStrategy_ {};

template <typename T>
using AttackStrategy = StrategyConditional<AttackStrategy_, T, Damagingable<T>>;

template <typename T>
concept is_attack_strategy = Strategable<AttackStrategy, T, ActionStatus, Object*, Object*>;

template <>
struct AttackStrategy_<Default> {
    constexpr ActionStatus operator()(Damagingable auto& obj, Object* owner, Object* target) const;
};
