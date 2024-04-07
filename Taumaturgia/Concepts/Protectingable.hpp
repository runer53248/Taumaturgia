#pragma once
#include "Taumaturgia/Concepts/Helpers/trait_accessable.hpp"
#include "Taumaturgia/Traits/ProtectionTraits.hpp"
#include "Taumaturgia/Types/Protection.hpp"

template <typename T>
concept Protectingable = trait_accessable<T, traits::accessProtection, Protection>;
