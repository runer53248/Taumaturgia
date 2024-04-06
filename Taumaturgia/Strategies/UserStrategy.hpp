#pragma once
#include <concepts>
#include "Taumaturgia/Concepts/Typeable.hpp"

enum class ActionStatus;

struct Default;
class Object;

template <typename TYPE, typename T>
struct UserStrategy_ {};

template <template <typename, typename> typename Strategy, typename TYPE, typename UserType>
concept UserStrategy_typeable = requires(Strategy<TYPE, UserType> strategy, UserType& type, Object* owner, Object* target) {
    { strategy.operator()(type, owner, target) } -> std::same_as<ActionStatus>;
};

template <template <typename> typename Strategy, typename UserType>
concept UserStrategy_able = requires(Strategy<UserType> strategy, UserType& type, Object* owner, Object* target) {
    { strategy.operator()(type, owner, target) } -> std::same_as<ActionStatus>;
};

template <typename TYPE, typename T>
using UserStrategy = std::conditional_t<
    getType_or_custom_accessable<T, TYPE>,
    std::conditional_t<
        UserStrategy_typeable<UserStrategy_, TYPE, T>,
        UserStrategy_<TYPE, T>,
        UserStrategy_<TYPE, Default> >,
    UserStrategy_<TYPE, T> >;

template <typename TYPE, typename T, bool CONCEPT>
using UserStrategyWithConcept = std::conditional_t<
    CONCEPT,
    std::conditional_t<
        UserStrategy_typeable<UserStrategy_, TYPE, T>,
        UserStrategy_<TYPE, T>,
        UserStrategy_<TYPE, Default> >,
    UserStrategy_<TYPE, T> >;

// template <typename TYPE, typename T>
// concept is_user_strategy = UserStrategy_typeable<UserStrategy, TYPE, T>;  // unused

template <typename TYPE>
struct UserStrategy_<TYPE, Default> {
    void operator()(getType_or_custom_accessable<TYPE> auto& obj) const;
};
