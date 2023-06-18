#pragma once
#include <concepts>
#include "../Concepts/Healingable.hpp"
#include "../Concepts/Types/Enums/ActionStatus.hpp"

struct Default;
struct Object;

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

template <>
struct HealStrategy_<Default> {
    ActionStatus operator()(Healingable auto& obj, Object* owner, Object* target) const;
};
