#pragma once
#include "Taumaturgia/Strategies/Concepts/Strategable.hpp"

struct Default;

template <template <typename> typename STRATEGY, typename T, bool CONCEPT, bool CUSTOM_CONCEPT>
using StrategyConditional = std::conditional_t<
    CONCEPT,
    std::conditional_t<
        CUSTOM_CONCEPT,
        STRATEGY<T>,
        STRATEGY<Default> >,
    STRATEGY<T> >;

template <template <typename, typename> typename STRATEGY, typename TYPE, typename T, bool CONCEPT, bool CUSTOM_CONCEPT>
using TypeStrategyConditional = std::conditional_t<
    CONCEPT,
    std::conditional_t<
        CUSTOM_CONCEPT,
        STRATEGY<TYPE, T>,
        STRATEGY<TYPE, Default> >,
    STRATEGY<TYPE, T> >;
