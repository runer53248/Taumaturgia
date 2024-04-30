#pragma once
#include <concepts>
#include <optional>
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"
#include "Taumaturgia/Traits/HealthTraits.hpp"

enum class AliveStatus : signed char;

template <typename T>
struct AliveStrategy_ {};

template <typename T>
using AliveStrategy = std::conditional_t<
    Livingable<T>,
    std::conditional_t<
        Strategable<AliveStrategy_, T, std::optional<AliveStatus>>,
        AliveStrategy_<T>,
        AliveStrategy_<Default>>,
    AliveStrategy_<T>>;

template <typename T>
concept is_alive_strategy = Strategable<AliveStrategy, T, std::optional<AliveStatus>>;

template <>
struct AliveStrategy_<Default> {
    constexpr std::optional<AliveStatus> operator()(Livingable auto& obj) const;
};
