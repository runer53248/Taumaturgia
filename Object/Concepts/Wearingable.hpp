#pragma once
#include <type_traits>
#include "Traits/ArmorWearTraits.hpp"
#include "Types/ProtectionContainer.hpp"

template <typename T>
concept Wearingable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { traits::accessArmorWear::get(x) } -> same_as_ref<ProtectionContainer>;
    { traits::accessArmorWear::get(y) } -> same_as_ref<const ProtectionContainer>;
};
