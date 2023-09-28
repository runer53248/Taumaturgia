#pragma once
#include <type_traits>
#include "Traits/ArmorWearTraits.hpp"
#include "Types/ProtectionContainer.hpp"

template <typename T>
concept Wearingable = requires(T x) {
    traits::accessArmorWear::get(x);
    { traits::accessArmorWear::get(x) } -> same_as_ref<ProtectionContainer>;
};
