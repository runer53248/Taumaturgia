#pragma once
#include "Object/Concepts/Traits/CureHealthTraits.hpp"
#include "Object/Concepts/Types/CureHealth.hpp"
#include "Object/Concepts/trait_accessible.hpp"

template <typename T>
concept Healingable = trait_accessible<T, traits::accessCureHealth, CureHealth>;
