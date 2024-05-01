#pragma once
#include <concepts>
#include <optional>
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"
#include "Taumaturgia/Traits/HealthTraits.hpp"

enum class AliveStatus : signed char;

template <typename T>
struct AliveStrategy_ {};

template <typename T>
using AliveStrategy = StrategyConditional<AliveStrategy_, T, Livingable<T>, std::optional<AliveStatus>>;

template <typename T>
concept is_alive_strategy = Strategable<AliveStrategy, T, std::optional<AliveStatus>>;
