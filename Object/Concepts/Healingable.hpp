#pragma once
#include <type_traits>
#include "Types/Health.hpp"

template <typename T>
concept Healingable = requires(T x) {
    x.cureHealth;
    std::is_same_v<decltype(T::cureHealth), Health>;
};
