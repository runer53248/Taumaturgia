#pragma once
#include <concepts>
#include "Taumaturgia/Concepts/Damagingable.hpp"
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"

template <typename T>
struct AttackStrategy_ {};

template <typename T>
using AttackStrategy = StrategyConditional<AttackStrategy_, T, Damagingable<T>>;

template <typename T>
concept is_attack_strategy = Strategable<AttackStrategy, T>;

template <>
struct AttackStrategy_<Default> {
    ActionStatus operator()(Damagingable auto& obj, Object* owner, Object* target) const;
};
