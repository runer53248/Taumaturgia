#pragma once
#include <concepts>
#include "Taumaturgia/Concepts/Restoringable.hpp"
#include "Taumaturgia/Strategies/Concepts/Strategable.hpp"

struct Default;

template <typename T>
struct RestoreStrategy_ {};

template <typename T>
using RestoreStrategy = std::conditional_t<
    Restoringable<T>,
    std::conditional_t<
        Strategable<RestoreStrategy_, T>,
        RestoreStrategy_<T>,
        RestoreStrategy_<Default> >,
    RestoreStrategy_<T> >;

template <typename T>
concept is_restore_strategy = Strategable<RestoreStrategy, T>;

template <>
struct RestoreStrategy_<Default> {
    ActionStatus operator()(Restoringable auto& obj, Object* owner, Object* target) const;
};
