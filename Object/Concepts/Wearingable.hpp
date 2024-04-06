#pragma once
#include "Object/Concepts/Traits/ArmorWearTraits.hpp"
#include "Object/Concepts/Types/WearContainer.hpp"
#include "Object/Concepts/trait_accessable.hpp"

template <typename T>
concept Wearingable = trait_accessable<T, traits::accessArmorWear, WearContainer>;
