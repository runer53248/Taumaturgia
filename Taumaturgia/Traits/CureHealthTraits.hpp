#pragma once
#include "Concepts/CureHealthConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

#ifdef WITH_ADD_PROPERTIES

#include "UserTypeTraits.hpp"
using Healingable_trait = traits::accessType<CureHealth>;
template <typename T>
concept Healingable = accessType_trait_able<T, CureHealth>;

#else

#include "Structs/accessCureHealth.hpp"
using Healingable_trait = traits::accessCureHealth;
template <typename T>
concept Healingable = trait_accessable<T, Healingable_trait, CureHealth>;

#endif
