#pragma once
#include <type_traits>
#include "Types/Health.hpp"

template <typename T>
concept Livingable = requires(T x) {
    x.hp;
    std::is_same_v<decltype(T::hp), Health>;
};
