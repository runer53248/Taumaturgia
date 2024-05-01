#pragma once
#include <concepts>
#include <optional>
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"
#include "Taumaturgia/Traits/UserTypeTraits.hpp"

template <typename TYPE, typename T, typename RET>
struct UserStrategy_ {};

template <typename TYPE, typename T, bool CONCEPT, typename RET, typename... Args>
using UserStrategy = TypeStrategyConditional<UserStrategy_, TYPE, T, CONCEPT, RET, Args...>;
