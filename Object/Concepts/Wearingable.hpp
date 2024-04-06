#pragma once
#include "Object/Concepts/Traits/ArmorWearTraits.hpp"
#include "Object/Concepts/Types/WearContainer.hpp"
#include "Object/Concepts/trait_accessible.hpp"

template <typename T>
concept Wearingable = trait_accessible<T, traits::accessArmorWear, WearContainer>;
