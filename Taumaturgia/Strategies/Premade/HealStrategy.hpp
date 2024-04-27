#pragma once
#include <concepts>
#include "Taumaturgia/Traits/CureHealthTraits.hpp"
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"

template <typename T>
struct HealStrategy_ {};

template <typename T>
using HealStrategy = StrategyConditional<HealStrategy_, T, Healingable<T>>;

template <typename T>
concept is_heal_strategy = Strategable<HealStrategy, T, ActionStatus, Object*, Object*>;

template <>
struct HealStrategy_<Default> {
    constexpr ActionStatus operator()(Healingable auto& obj, Object* owner, Object* target) const;
};
