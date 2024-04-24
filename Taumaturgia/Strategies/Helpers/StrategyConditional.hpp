#pragma once
#include "Taumaturgia/Strategies/Concepts/Strategable.hpp"

struct Default;

template <template <typename> typename STRATEGY, typename T, bool CONCEPT>
using StrategyConditional = std::conditional_t<
    CONCEPT,
    std::conditional_t<
        Strategable<STRATEGY, T>,
        STRATEGY<T>,
        STRATEGY<Default> >,
    STRATEGY<T> >;
