#pragma once
#include "Concepts/ArmorWearConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

#ifdef WITH_ADD_PROPERTIES

#include "UserTypeTraits.hpp"
using Wearingable_trait = traits::accessType<WearContainer>;
template <typename T>
concept Wearingable = accessType_trait_able<T, WearContainer>;

#else

#include "Structs/accessArmorWear.hpp"
using Wearingable_trait = traits::accessArmorWear;
template <typename T>
concept Wearingable = trait_accessable<T, Wearingable_trait, WearContainer>;

#endif
