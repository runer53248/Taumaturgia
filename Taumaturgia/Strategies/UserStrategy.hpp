#pragma once
#include <concepts>
#include <optional>
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"
#include "Taumaturgia/Traits/UserTypeTraits.hpp"

template <typename TYPE, typename T, typename RET>
struct UserStrategy_{};

template <typename TYPE, typename T, bool CONCEPT, typename RET, typename... Args>
using UserStrategy = TypeStrategyConditional<UserStrategy_, TYPE, T, CONCEPT, RET, Args...>;

struct Default;
class Object;
enum class ActionStatus;
enum class AliveStatus : signed char;

template <typename TYPE>
struct UserStrategy_<TYPE, Default, ActionStatus> {
    constexpr ActionStatus operator()(accessType_trait_able<TYPE> auto& obj, Object* owner, Object* target) const;
};

template <typename TYPE>
struct UserStrategy_<TYPE, Default, std::optional<AliveStatus>> {
    constexpr std::optional<AliveStatus> operator()(accessType_trait_able<TYPE> auto& obj) const;
};
