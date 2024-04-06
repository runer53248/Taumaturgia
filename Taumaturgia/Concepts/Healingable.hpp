#pragma once
#include "Taumaturgia/Concepts/Helpers/trait_accessable.hpp"
#include "Taumaturgia/Concepts/Traits/CureHealthTraits.hpp"
#include "Taumaturgia/Concepts/Types/CureHealth.hpp"

template <typename T>
concept Healingable = trait_accessable<T, traits::accessCureHealth, CureHealth>;
