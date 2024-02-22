#pragma once
#include <type_traits>
#include "Traits/ArmorWearTraits.hpp"
#include "Types/ProtectionContainer.hpp"

template <typename T>
concept Wearingable = requires(std::remove_cvref_t<T> x) {
    { traits::accessArmorWear::get(x) } -> same_as_ref<ProtectionContainer>;
    { traits::accessArmorWear::get(std::as_const(x)) } -> same_as_ref<const ProtectionContainer>;
};
