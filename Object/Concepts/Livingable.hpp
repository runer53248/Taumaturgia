#pragma once
#include "Object/Concepts/Traits/HealthTraits.hpp"
#include "Object/Concepts/Types/Health.hpp"
#include "Object/Concepts/trait_accessible.hpp"

template <typename T>
concept Livingable = trait_accessible<T, traits::accessHealth, Health>;
