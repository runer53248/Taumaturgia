#pragma once
#include <type_traits>
#include "Types/ArmorClassContainer.hpp"

template <typename T>
concept Wearingable = requires (T x) { 
    x.armorWear;
    std::is_same_v<decltype(T::armorWear), ArmorClassContainer>;
};
