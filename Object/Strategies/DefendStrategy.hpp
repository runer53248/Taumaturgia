#pragma once
#include <concepts>
#include "../Concepts/Protectingable.hpp"

enum class ActionStatus;

struct Default;
class Object;

template <typename T>
struct DefendStrategy_ {};

template <template <typename> typename Strategy, typename UserType>
concept DefendStrategable = requires(Strategy<UserType> strategy, UserType& type, Object* owner, Object* target) {
    { strategy.operator()(type, owner, target) } -> std::same_as<ActionStatus>;
};

template <typename T>
using DefendStrategy = std::conditional_t<
    Protectingable<T>,
    std::conditional_t<
        DefendStrategable<DefendStrategy_, T>,
        DefendStrategy_<T>,
        DefendStrategy_<Default> >,
    DefendStrategy_<T> >;

template <typename T>
concept is_defend_strategy = DefendStrategable<DefendStrategy, T>;

template <>
struct DefendStrategy_<Default> {
    ActionStatus operator()(Protectingable auto& obj, Object* owner, Object* target) const;
};
