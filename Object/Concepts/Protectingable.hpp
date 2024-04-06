#pragma once
#include "Object/Concepts/Helpers/trait_accessable.hpp"
#include "Object/Concepts/Traits/ProtectionTraits.hpp"
#include "Object/Concepts/Types/Protection.hpp"

template <typename T>
concept Protectingable = trait_accessable<T, traits::accessProtection, Protection>;
