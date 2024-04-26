#pragma once
#include <concepts>
#include "Taumaturgia/Traits/ArmorWearTraits.hpp"
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"

template <typename T>
struct WearStrategy_ {};

template <typename T>
using WearStrategy = StrategyConditional<WearStrategy_, T, Wearingable<T>>;

template <typename T>
concept is_wear_strategy = Strategable<WearStrategy, T, ActionStatus, Object*, Object*>;

template <>
struct WearStrategy_<Default> {
    ActionStatus operator()(Wearingable auto& obj, Object* owner, Object* target) const;
};
