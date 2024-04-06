#pragma once
#include "Taumaturgia/Concepts/Helpers/trait_accessable.hpp"
#include "Taumaturgia/Concepts/Traits/HealthTraits.hpp"
#include "Taumaturgia/Concepts/Types/Health.hpp"

template <typename T>
concept Livingable = trait_accessable<T, traits::accessHealth, Health>;
