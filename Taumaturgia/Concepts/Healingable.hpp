#pragma once
#include "Taumaturgia/Concepts/Helpers/trait_accessable.hpp"
#include "Taumaturgia/Traits/CureHealthTraits.hpp"
#include "Taumaturgia/Types/CureHealth.hpp"

template <typename T>
concept Healingable = trait_accessable<T, traits::accessCureHealth, CureHealth>;
