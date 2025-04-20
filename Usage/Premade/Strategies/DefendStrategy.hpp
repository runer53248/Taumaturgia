#pragma once
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"

class Object;
enum class ActionStatus;

template <typename T>
struct DefendStrategy_ {};

template <typename T>
concept is_custom_defend_strategy = Strategable<DefendStrategy_, T, ActionStatus, Object*, Object*>;

template <typename T>
using DefendStrategy = StrategyConditional<DefendStrategy_, T, Protectingable<T>, is_custom_defend_strategy<T>>;
