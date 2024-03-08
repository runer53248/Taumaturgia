#pragma once
#include <concepts>
#include "../Concepts/Typeable.hpp"

enum class ActionStatus;

struct Default;
class Object;

template <typename TYPE, typename T>
struct UserStrategy_ {};

template <template <typename, typename> typename Strategy, typename TYPE, typename UserType>
concept UserStrategable = requires(Strategy<TYPE, UserType> strategy, UserType& type, Object* owner, Object* target) {
    { strategy.operator()(type, owner, target) } -> std::same_as<ActionStatus>;
};

template <typename TYPE, typename T>
using UserStrategy = std::conditional_t<
    Typeable<T, TYPE>,
    std::conditional_t<
        UserStrategable<UserStrategy_, TYPE, T>,
        UserStrategy_<TYPE, T>,
        UserStrategy_<TYPE, Default> >,
    UserStrategy_<TYPE, T> >;

template <typename TYPE, typename T>
concept is_user_strategy = UserStrategable<UserStrategy, TYPE, T>;  // unused

template <typename TYPE>
struct UserStrategy_<TYPE, Default> {
    void operator()(Typeable<TYPE> auto& obj) const;
};
