#pragma once
#include "Object/Concepts/Traits/CureHealthTraits.hpp"
#include "Object/Concepts/Types/CureHealth.hpp"
#include "Object/Concepts/trait_accessable.hpp"

template <typename T>
concept Healingable = trait_accessable<T, traits::accessCureHealth, CureHealth>;
