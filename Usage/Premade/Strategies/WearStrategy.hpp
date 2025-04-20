#pragma once
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"

class Object;
enum class ActionStatus;

template <typename T>
struct WearStrategy_ {};

template <typename T>
concept is_custom_wear_strategy = Strategable<WearStrategy_, T, ActionStatus, Object*, Object*>;

template <typename T>
using WearStrategy = StrategyConditional<WearStrategy_, T, Wearingable<T>, is_custom_wear_strategy<T>>;
