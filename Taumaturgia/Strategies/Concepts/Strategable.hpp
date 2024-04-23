#pragma once
#include <concepts>

enum class ActionStatus;
class Object;

template <template <typename> typename Strategy, typename T>
concept Strategable = requires(Strategy<T> strategy, T& type, Object* owner, Object* target) {
    { strategy.operator()(type, owner, target) } -> std::same_as<ActionStatus>;
};

template <template <typename, typename> typename Strategy, typename TYPE, typename T>
concept TypeStrategable = requires(Strategy<TYPE, T> strategy, T& type, Object* owner, Object* target) {
    { strategy.operator()(type, owner, target) } -> std::same_as<ActionStatus>;
};
