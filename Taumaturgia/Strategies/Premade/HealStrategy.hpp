#pragma once
#include <concepts>
#include "Taumaturgia/Concepts/Healingable.hpp"
#include "Taumaturgia/Strategies/Concepts/Strategable.hpp"

struct Default;

template <typename T>
struct HealStrategy_ {};

template <typename T>
using HealStrategy = std::conditional_t<
    Healingable<T>,
    std::conditional_t<
        Strategable<HealStrategy_, T>,
        HealStrategy_<T>,
        HealStrategy_<Default> >,
    HealStrategy_<T> >;

template <typename T>
concept is_heal_strategy = Strategable<HealStrategy, T>;

template <>
struct HealStrategy_<Default> {
    ActionStatus operator()(Healingable auto& obj, Object* owner, Object* target) const;
};
