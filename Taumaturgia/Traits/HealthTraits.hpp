#pragma once
#include "Concepts/HealthConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

#ifdef WITH_ADD_PROPERTIES

#include "UserTypeTraits.hpp"
using Livingable_trait = traits::accessType<Health>;
template <typename T>
concept Livingable = accessType_trait_able<T, Health>;

#else

#include "Structs/accessHealth.hpp"
using Livingable_trait = traits::accessHealth;
template <typename T>
concept Livingable = trait_accessable<T, Livingable_trait, Health>;

#endif
