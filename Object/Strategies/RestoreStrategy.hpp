#pragma once
#include <concepts>
#include "../Concepts/Restoringable.hpp"

enum class ActionStatus;

struct Default;
class Object;

template <typename T>
struct RestoreStrategy_ {};

template <template <typename> typename Strategy, typename UserType>
concept RestoreStrategable = requires(Strategy<UserType> strategy, UserType& type, Object* owner, Object* target) {
    { strategy.operator()(type, owner, target) } -> std::same_as<ActionStatus>;
};

template <typename T>
using RestoreStrategy = std::conditional_t<
    Restoringable<T>,
    std::conditional_t<
        RestoreStrategable<RestoreStrategy_, T>,
        RestoreStrategy_<T>,
        RestoreStrategy_<Default> >,
    RestoreStrategy_<T> >;

template <typename T>
concept is_restore_strategy = RestoreStrategable<RestoreStrategy, T>;

template <>
struct RestoreStrategy_<Default> {
    ActionStatus operator()(Restoringable auto& obj, Object* owner, Object* target) const;
};
