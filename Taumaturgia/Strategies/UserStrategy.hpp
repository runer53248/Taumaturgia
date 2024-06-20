#pragma once
#include <concepts>
#include <optional>
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"
#include "Taumaturgia/Traits/UserTypeTraits.hpp"

template <typename TYPE, typename T>
struct UserStrategy_ {};

template <typename TYPE, typename T, typename RET, typename... Args>
concept is_custom_type_strategy = TypeStrategable<UserStrategy_, TYPE, T, RET, Args...>;

template <typename TYPE, typename T, bool CONCEPT, typename RET, typename... Args>
using UserStrategy = TypeStrategyConditional<UserStrategy_, TYPE, T, CONCEPT, is_custom_type_strategy<TYPE, T, RET, Args...>>;
