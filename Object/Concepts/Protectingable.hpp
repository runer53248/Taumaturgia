#pragma once
#include "Object/Concepts/Traits/ProtectionTraits.hpp"
#include "Object/Concepts/Types/Protection.hpp"
#include "Object/Concepts/trait_accessable.hpp"

template <typename T>
concept Protectingable = trait_accessable<T, traits::accessProtection, Protection>;
