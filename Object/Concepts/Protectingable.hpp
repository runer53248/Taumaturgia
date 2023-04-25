#pragma once
#include <type_traits>
#include "Types/Protection.hpp"

template <typename T>
concept Protectingable = requires(T x) {
    x.protection;
    std::is_same_v<decltype(T::protection), Protection>;
};
