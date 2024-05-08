#pragma once
#include "Concepts/ProtectionConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

#ifdef WITH_ADD_PROPERTIES

#include "UserTypeTraits.hpp"
using Protectingable_trait = traits::accessType<Protection>;
template <typename T>
concept Protectingable = accessType_trait_able<T, Protection>;

#else

#include "Structs/accessProtection.hpp"
using Protectingable_trait = traits::accessProtection;
template <typename T>
concept Protectingable = trait_accessable<T, Protectingable_trait, Protection>;

#endif
