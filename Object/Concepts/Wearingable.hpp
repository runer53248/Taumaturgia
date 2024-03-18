#pragma once
#include <type_traits>
#include "Traits/ArmorWearTraits.hpp"
#include "Types/WearContainer.hpp"

template <typename T>
concept Wearingable = requires(std::remove_cvref_t<T> x) {
    { traits::accessArmorWear::get(x) } -> same_as_ref<WearContainer>;
    { traits::accessArmorWear::get(std::as_const(x)) } -> same_as_ref<const WearContainer>;
};
