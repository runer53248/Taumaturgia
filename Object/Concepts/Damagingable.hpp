#pragma once
#include <type_traits>
#include "Types/Damage.hpp"

template <typename T>
concept Damagingable = requires(T x) {
    x.dmg;
    std::is_same_v<decltype(T::dmg), Damage>;
};
