#pragma once
#include "Object/Concepts/Traits/HealthTraits.hpp"
#include "Object/Concepts/Types/Health.hpp"
#include "Object/Concepts/trait_accessable.hpp"

template <typename T>
concept Livingable = trait_accessable<T, traits::accessHealth, Health>;
