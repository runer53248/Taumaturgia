#pragma once
#include "Taumaturgia/Traits/ArmorWearTraits.hpp"
#include "Taumaturgia/Traits/Helpers/trait_accessable.hpp"
#include "Taumaturgia/Types/WearContainer.hpp"

template <typename T>
concept Wearingable = trait_accessable<T, traits::accessArmorWear, WearContainer>;
