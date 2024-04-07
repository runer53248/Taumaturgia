#pragma once
#include "Taumaturgia/Concepts/Helpers/trait_accessable.hpp"
#include "Taumaturgia/Traits/ArmorWearTraits.hpp"
#include "Taumaturgia/Types/WearContainer.hpp"

template <typename T>
concept Wearingable = trait_accessable<T, traits::accessArmorWear, WearContainer>;
