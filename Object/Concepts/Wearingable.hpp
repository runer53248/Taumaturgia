#pragma once
#include "Object/Concepts/Helpers/trait_accessable.hpp"
#include "Object/Concepts/Traits/ArmorWearTraits.hpp"
#include "Object/Concepts/Types/WearContainer.hpp"

template <typename T>
concept Wearingable = trait_accessable<T, traits::accessArmorWear, WearContainer>;
