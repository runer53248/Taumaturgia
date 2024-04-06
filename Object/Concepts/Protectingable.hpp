#pragma once
#include "Object/Concepts/Traits/ProtectionTraits.hpp"
#include "Object/Concepts/Types/Protection.hpp"
#include "Object/Concepts/trait_accessible.hpp"

template <typename T>
concept Protectingable = trait_accessible<T, traits::accessProtection, Protection>;
