#pragma once
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"

class Object;
enum class ActionStatus;

template <typename T>
struct AttackStrategy_ {};

template <typename T>
concept is_custom_attack_strategy = Strategable<AttackStrategy_, T, ActionStatus, Object*, Object*>;

template <typename T>
using AttackStrategy = StrategyConditional<AttackStrategy_, T, Damagingable<T>, is_custom_attack_strategy<T>>;
