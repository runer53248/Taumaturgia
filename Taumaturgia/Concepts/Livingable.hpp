#pragma once
#include "Taumaturgia/Traits/HealthTraits.hpp"
#include "Taumaturgia/Traits/Helpers/trait_accessable.hpp"
#include "Taumaturgia/Types/Health.hpp"

template <typename T>
concept Livingable = trait_accessable<T, traits::accessHealth, Health>;
