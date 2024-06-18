#pragma once
#include <concepts>
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"

class Object;
enum class ActionStatus;

template <typename T>
struct AttackStrategy_ {};

template <typename T>
using AttackStrategy = StrategyConditional<AttackStrategy_, T, Damagingable<T>, ActionStatus, Object*, Object*>;

template <typename T>
concept is_attack_strategy = Strategable<AttackStrategy, T, ActionStatus, Object*, Object*>;
