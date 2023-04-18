#pragma once
#include <concepts>
#include "../Concepts/Livingable.hpp"

struct Default;
struct Object;

template <typename T>
struct AliveStrategy_ {};

template <template <typename> typename Strategy, typename UserType>
concept AliveStrategable = requires(Strategy<UserType> strategy, UserType& type) {
    { strategy.operator()(type) } -> std::same_as<std::optional<bool>>;
};

template <typename T>
using AliveStrategy = std::conditional_t<
    Livingable<T>,
    std::conditional_t<
        AliveStrategable<AliveStrategy_, T>,
        AliveStrategy_<T>,
        AliveStrategy_<Default>>,
    AliveStrategy_<T>>;

template <>
struct AliveStrategy_<Default> {
    std::optional<bool> operator()(Livingable auto& obj) const;
};
