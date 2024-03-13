#pragma once
#include <concepts>
#include "Object/Concepts/Healingable.hpp"

enum class ActionStatus;

struct Default;
class Object;

template <typename T>
struct HealStrategy_ {};

template <template <typename> typename Strategy, typename UserType>
concept HealStrategable = requires(Strategy<UserType> strategy, UserType& type, Object* owner, Object* target) {
    { strategy.operator()(type, owner, target) } -> std::same_as<ActionStatus>;
};

template <typename T>
using HealStrategy = std::conditional_t<
    Healingable<T>,
    std::conditional_t<
        HealStrategable<HealStrategy_, T>,
        HealStrategy_<T>,
        HealStrategy_<Default> >,
    HealStrategy_<T> >;

template <typename T>
concept is_heal_strategy = HealStrategable<HealStrategy, T>;

template <>
struct HealStrategy_<Default> {
    ActionStatus operator()(Healingable auto& obj, Object* owner, Object* target) const;
};
