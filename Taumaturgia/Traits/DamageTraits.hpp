#pragma once
#include "Concepts/DamageConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

#ifdef WITH_ADD_PROPERTIES

#include "UserTypeTraits.hpp"
using Damagingable_trait = traits::accessType<Damage>;
template <typename T>
concept Damagingable = accessType_trait_able<T, Damage>;

#else

#include "Structs/accessDamage.hpp"
using Damagingable_trait = traits::accessDamage;
template <typename T>
concept Damagingable = trait_accessable<T, Damagingable_trait, Damage>;

#endif
