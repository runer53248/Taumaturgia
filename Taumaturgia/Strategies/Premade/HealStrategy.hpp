#pragma once
#include <concepts>
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"
#include "Taumaturgia/Traits/CureHealthTraits.hpp"

class Object;
enum class ActionStatus;

template <typename T>
struct HealStrategy_ {};

template <typename T>
using HealStrategy = StrategyConditional<HealStrategy_, T, Healingable<T>, ActionStatus, Object*, Object*>;

template <typename T>
concept is_heal_strategy = Strategable<HealStrategy, T, ActionStatus, Object*, Object*>;
