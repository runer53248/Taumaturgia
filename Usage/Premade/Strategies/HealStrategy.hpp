#pragma once
#include <concepts>
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"

class Object;
enum class ActionStatus;

template <typename T>
struct HealStrategy_ {};

template <typename T>
concept is_custom_heal_strategy = Strategable<HealStrategy_, T, ActionStatus, Object*, Object*>;

template <typename T>
using HealStrategy = StrategyConditional<HealStrategy_, T, Healingable<T>, is_custom_heal_strategy<T>>;
