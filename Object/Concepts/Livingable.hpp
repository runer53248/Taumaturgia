#pragma once
#include "Object/Concepts/Helpers/trait_accessable.hpp"
#include "Object/Concepts/Traits/HealthTraits.hpp"
#include "Object/Concepts/Types/Health.hpp"

template <typename T>
concept Livingable = trait_accessable<T, traits::accessHealth, Health>;
