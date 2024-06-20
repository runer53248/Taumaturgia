#pragma once
#include <concepts>

// template <typename RET, typename T, typename... Args>
// struct invoke_scheme {
//     using return_type = RET;
//     using type = T;
//     using args_types = list<T, Args...>;
// };

template <template <typename> typename Strategy, typename T, typename RET, typename... Args>
concept Strategable = std::is_invocable_r_v<RET, Strategy<std::remove_const_t<T>>, T&, Args...>;

template <template <typename> typename Strategy, typename T, typename RET, typename TA, typename... Args>
concept Strategable_template = requires(Strategy<std::remove_const_t<T>> strategy, T& type, Args... args) {
    { strategy.template operator()<TA{}>(type, args...) } -> std::same_as<RET>;
};

template <template <typename, typename> typename Strategy, typename TYPE, typename T, typename RET, typename... Args>
concept TypeStrategable = std::is_invocable_r_v<RET, Strategy<TYPE, std::remove_const_t<T>>, T&, Args...>;
