#pragma once
#include <concepts>
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"

class Object;
enum class ActionStatus;

template <typename T>
struct DefendStrategy_ {};

template <typename T>
using DefendStrategy = StrategyConditional<DefendStrategy_, T, Protectingable<T>, ActionStatus, Object*, Object*>;

template <typename T>
concept is_defend_strategy = Strategable<DefendStrategy, T, ActionStatus, Object*, Object*>;
