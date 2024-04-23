#pragma once
#include <concepts>
#include "Taumaturgia/Concepts/Protectingable.hpp"
#include "Taumaturgia/Strategies/Concepts/Strategable.hpp"

struct Default;

template <typename T>
struct DefendStrategy_ {};

template <typename T>
using DefendStrategy = std::conditional_t<
    Protectingable<T>,
    std::conditional_t<
        Strategable<DefendStrategy_, T>,
        DefendStrategy_<T>,
        DefendStrategy_<Default> >,
    DefendStrategy_<T> >;

template <typename T>
concept is_defend_strategy = Strategable<DefendStrategy, T>;

template <>
struct DefendStrategy_<Default> {
    ActionStatus operator()(Protectingable auto& obj, Object* owner, Object* target) const;
};
