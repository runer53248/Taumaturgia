#pragma once
#include <concepts>
#include "Taumaturgia/Strategies/Concepts/Strategable.hpp"
#include "Taumaturgia/Traits/UserTypeTraits.hpp"

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
    constexpr ActionStatus operator()(accessType_trait_able<TYPE> auto& obj, Object* owner, Object* target) const;
};
