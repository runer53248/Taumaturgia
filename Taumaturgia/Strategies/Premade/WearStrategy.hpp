#pragma once
#include <concepts>
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"
#include "Taumaturgia/Traits/ArmorWearTraits.hpp"

class Object;
enum class ActionStatus;

template <typename T>
struct WearStrategy_ {};

template <typename T>
using WearStrategy = StrategyConditional<WearStrategy_, T, Wearingable<T>, ActionStatus, Object*, Object*>;

template <typename T>
concept is_wear_strategy = Strategable<WearStrategy, T, ActionStatus, Object*, Object*>;

template <>
struct WearStrategy_<Default> {
    constexpr ActionStatus operator()(Wearingable auto& obj, Object* owner, Object* target) const;
};
