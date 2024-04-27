#pragma once
#include <concepts>
#include "Taumaturgia/Traits/ProtectionTraits.hpp"
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"

template <typename T>
struct DefendStrategy_ {};

template <typename T>
using DefendStrategy = StrategyConditional<DefendStrategy_, T, Protectingable<T>>;

template <typename T>
concept is_defend_strategy = Strategable<DefendStrategy, T, ActionStatus, Object*, Object*>;

template <>
struct DefendStrategy_<Default> {
    constexpr ActionStatus operator()(Protectingable auto& obj, Object* owner, Object* target) const;
};
