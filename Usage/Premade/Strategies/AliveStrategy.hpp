#pragma once
#include <optional>
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"

enum class AliveStatus : signed char;

template <typename T>
struct AliveStrategy_ {};

template <typename T>
concept is_custom_alive_strategy = Strategable<AliveStrategy_, T, std::optional<AliveStatus>>;

template <typename T>
using AliveStrategy = StrategyConditional<AliveStrategy_, T, Livingable<T>, is_custom_alive_strategy<T>>;
