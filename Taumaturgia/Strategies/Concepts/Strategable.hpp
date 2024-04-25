#pragma once
#include <concepts>

template <template <typename> typename Strategy, typename T, typename RET, typename... Args>
concept Strategable = requires(Strategy<T> strategy, T& type, Args... args) {
    { strategy.operator()(type, args...) } -> std::same_as<RET>;
};

template <template <typename> typename Strategy, typename T, typename RET, typename TEMP>
concept Strategable_template = requires(Strategy<T> strategy, T& type) {
    { strategy.template operator()<TEMP{}>(type) } -> std::same_as<RET>;
};

template <template <typename, typename> typename Strategy, typename TYPE, typename T, typename RET, typename... Args>
concept TypeStrategable = requires(Strategy<TYPE, T> strategy, T& type, Args... args) {
    { strategy.operator()(type, args...) } -> std::same_as<RET>;
};
