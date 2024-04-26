#pragma once
#include <concepts>
#include "Taumaturgia/Traits/RestoreEffectsTraits.hpp"
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"

template <typename T>
struct RestoreStrategy_ {};

template <typename T>
using RestoreStrategy = StrategyConditional<RestoreStrategy_, T, Restoringable<T>>;

template <typename T>
concept is_restore_strategy = Strategable<RestoreStrategy, T, ActionStatus, Object*, Object*>;

template <>
struct RestoreStrategy_<Default> {
    ActionStatus operator()(Restoringable auto& obj, Object* owner, Object* target) const;
};
