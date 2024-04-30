#pragma once
#include "Taumaturgia/Strategies/Concepts/Strategable.hpp"

struct Default;

template <template <typename> typename STRATEGY, typename T, bool CONCEPT, typename RET, typename... Args>
using StrategyConditional = std::conditional_t<
    CONCEPT,
    std::conditional_t<
        Strategable<STRATEGY, T, RET, Args...>,
        STRATEGY<T>,
        STRATEGY<Default> >,
    STRATEGY<T> >;

template <template <typename, typename, typename> typename STRATEGY, typename TYPE, typename T, bool CONCEPT, typename RET, typename... Args>
using TypeStrategyConditional = std::conditional_t<
    CONCEPT,
    std::conditional_t<
        TypeStrategable<STRATEGY, TYPE, T, RET, Args...>,
        STRATEGY<TYPE, T, RET>,
        STRATEGY<TYPE, Default, RET> >,
    STRATEGY<TYPE, T, RET> >;
