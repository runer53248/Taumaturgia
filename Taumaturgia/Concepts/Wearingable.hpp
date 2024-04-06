#pragma once
#include "Taumaturgia/Concepts/Helpers/trait_accessable.hpp"
#include "Taumaturgia/Concepts/Traits/ArmorWearTraits.hpp"
#include "Taumaturgia/Concepts/Types/WearContainer.hpp"

template <typename T>
concept Wearingable = trait_accessable<T, traits::accessArmorWear, WearContainer>;
