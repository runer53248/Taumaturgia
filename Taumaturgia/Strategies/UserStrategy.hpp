#pragma once
#include <concepts>
#include "Taumaturgia/Concepts/Typeable.hpp"
#include "Taumaturgia/Strategies/Concepts/Strategable.hpp"

struct Default;
struct Object;
enum class ActionStatus;

template <typename TYPE, typename T>
struct UserStrategy_ {};

template <typename TYPE, typename T, bool CONCEPT>
using UserStrategy = std::conditional_t<
    CONCEPT,
    std::conditional_t<
        TypeStrategable<UserStrategy_, TYPE, T, ActionStatus, Object*, Object*>,
        UserStrategy_<TYPE, T>,
        UserStrategy_<TYPE, Default> >,
    UserStrategy_<TYPE, T> >;

template <typename TYPE>
struct UserStrategy_<TYPE, Default> {
    void operator()(getType_or_custom_accessable<TYPE> auto& obj) const;  // ! not implemented?
};
