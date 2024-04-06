#pragma once
#include "Object/Concepts/Helpers/trait_accessable.hpp"
#include "Object/Concepts/Traits/CureHealthTraits.hpp"
#include "Object/Concepts/Types/CureHealth.hpp"

template <typename T>
concept Healingable = trait_accessable<T, traits::accessCureHealth, CureHealth>;
