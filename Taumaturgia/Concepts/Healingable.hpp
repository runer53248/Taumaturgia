#pragma once
#include "Taumaturgia/Traits/CureHealthTraits.hpp"
#include "Taumaturgia/Traits/Helpers/trait_accessable.hpp"
#include "Taumaturgia/Types/CureHealth.hpp"

template <typename T>
concept Healingable = trait_accessable<T, traits::accessCureHealth, CureHealth>;
