#pragma once
#include <type_traits>
#include "Types/Hp.hpp"

template <typename T>
concept Healingable = requires (T x) {
    x.cureHp;
    std::is_same_v<decltype(T::cureHp), Hp>;
};
