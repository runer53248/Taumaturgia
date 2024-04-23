#pragma once
#include <concepts>
#include "Taumaturgia/Concepts/Typeable.hpp"
#include "Taumaturgia/Strategies/Concepts/Strategable.hpp"

struct Default;

template <typename TYPE, typename T>
struct UserStrategy_ {};

template <typename TYPE, typename T>
using UserStrategy = std::conditional_t<
    getType_or_custom_accessable<T, TYPE>,
    std::conditional_t<
        TypeStrategable<UserStrategy_, TYPE, T>,
        UserStrategy_<TYPE, T>,
        UserStrategy_<TYPE, Default> >,
    UserStrategy_<TYPE, T> >;

template <typename TYPE, typename T, bool CONCEPT>
using UserStrategyWithConcept = std::conditional_t<
    CONCEPT,
    std::conditional_t<
        TypeStrategable<UserStrategy_, TYPE, T>,
        UserStrategy_<TYPE, T>,
        UserStrategy_<TYPE, Default> >,
    UserStrategy_<TYPE, T> >;

// template <typename TYPE, typename T>
// concept is_user_strategy = TypeStrategable<UserStrategy, TYPE, T>;  // unused

template <typename TYPE>
struct UserStrategy_<TYPE, Default> {
    void operator()(getType_or_custom_accessable<TYPE> auto& obj) const;
};
