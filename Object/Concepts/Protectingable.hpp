#pragma once
#include <type_traits>
#include "Types/ArmorClass.hpp"

template <typename T>
concept Protectingable = requires(T x) {
    x.ac;
    std::is_same_v<decltype(T::ac), ArmorClass>;
};
