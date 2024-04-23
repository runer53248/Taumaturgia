#pragma once
#include <concepts>
#include "Taumaturgia/Concepts/Damagingable.hpp"
#include "Taumaturgia/Strategies/Concepts/Strategable.hpp"

struct Default;

template <typename T>
struct AttackStrategy_ {};

template <typename T>
using AttackStrategy = std::conditional_t<
    Damagingable<T>,
    std::conditional_t<
        Strategable<AttackStrategy_, T>,
        AttackStrategy_<T>,
        AttackStrategy_<Default> >,
    AttackStrategy_<T> >;

template <typename T>
concept is_attack_strategy = Strategable<AttackStrategy, T>;

template <>
struct AttackStrategy_<Default> {
    ActionStatus operator()(Damagingable auto& obj, Object* owner, Object* target) const;
};
