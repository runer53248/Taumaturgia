#pragma once
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"

class Object;
enum class ActionStatus;

template <typename T>
struct RestoreStrategy_ {};

template <typename T>
concept is_custom_restore_strategy = Strategable<RestoreStrategy_, T, ActionStatus, Object*, Object*>;

template <typename T>
using RestoreStrategy = StrategyConditional<RestoreStrategy_, T, Restoringable<T>, is_custom_restore_strategy<T>>;
