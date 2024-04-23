#pragma once
#include <concepts>
#include "Taumaturgia/Concepts/Wearingable.hpp"
#include "Taumaturgia/Strategies/Concepts/Strategable.hpp"

struct Default;

template <typename T>
struct WearStrategy_ {};

template <typename T>
using WearStrategy = std::conditional_t<
    Wearingable<T>,
    std::conditional_t<
        Strategable<WearStrategy_, T>,
        WearStrategy_<T>,
        WearStrategy_<Default> >,
    WearStrategy_<T> >;

template <typename T>
concept is_wear_strategy = Strategable<WearStrategy, T>;

template <>
struct WearStrategy_<Default> {
    ActionStatus operator()(Wearingable auto& obj, Object* owner, Object* target) const;
};
