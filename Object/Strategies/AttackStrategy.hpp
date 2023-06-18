#pragma once
#include <concepts>
#include "../Concepts/Damagingable.hpp"

enum class ActionStatus;

struct Default;
struct Object;

template <typename T>
struct AttackStrategy_ {};

template <template <typename> typename Strategy, typename UserType>
concept AttackStrategable = requires(Strategy<UserType> strategy, UserType& type, Object* owner, Object* target) {
    { strategy.operator()(type, owner, target) } -> std::same_as<ActionStatus>;
};

template <typename T>
using AttackStrategy = std::conditional_t<
    Damagingable<T>,
    std::conditional_t<
        AttackStrategable<AttackStrategy_, T>,
        AttackStrategy_<T>,
        AttackStrategy_<Default> >,
    AttackStrategy_<T> >;

template <>
struct AttackStrategy_<Default> {
    ActionStatus operator()(Damagingable auto& obj, Object* owner, Object* target) const;
};
