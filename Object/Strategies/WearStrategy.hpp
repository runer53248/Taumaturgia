#pragma once
#include <concepts>
#include "../Concepts/Wearingable.hpp"

enum class ActionStatus;

struct Default;
class Object;

template <typename T>
struct WearStrategy_ {};

template <template <typename> typename Strategy, typename UserType>
concept WearStrategable = requires(Strategy<UserType> strategy, UserType& type, Object* owner, Object* target) {
    { strategy.operator()(type, owner, target) } -> std::same_as<ActionStatus>;
};

template <typename T>
using WearStrategy = std::conditional_t<
    Wearingable<T>,
    std::conditional_t<
        WearStrategable<WearStrategy_, T>,
        WearStrategy_<T>,
        WearStrategy_<Default> >,
    WearStrategy_<T> >;

template <>
struct WearStrategy_<Default> {
    ActionStatus operator()(Wearingable auto& obj, Object* owner, Object* target) const;
};
