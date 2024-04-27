#pragma once
#include "Taumaturgia/Strategies/Concepts/Strategable.hpp"

struct Default;
class Object;
enum class ActionStatus;

template <template <typename> typename STRATEGY, typename T, bool CONCEPT, typename RET = ActionStatus>
using StrategyConditional = std::conditional_t<
    CONCEPT,
    std::conditional_t<
        Strategable<STRATEGY, T, RET, Object*, Object*>,
        STRATEGY<T>,
        STRATEGY<Default> >,
    STRATEGY<T> >;
