#pragma once
#include <concepts>
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"
#include "Taumaturgia/Traits/RestoreEffectsTraits.hpp"

class Object;
enum class ActionStatus;

template <typename T>
struct RestoreStrategy_ {};

template <typename T>
using RestoreStrategy = StrategyConditional<RestoreStrategy_, T, Restoringable<T>, ActionStatus, Object*, Object*>;

template <typename T>
concept is_restore_strategy = Strategable<RestoreStrategy, T, ActionStatus, Object*, Object*>;

template <>
struct RestoreStrategy_<Default> {
    constexpr ActionStatus operator()(Restoringable auto& obj, Object* owner, Object* target) const;
};
