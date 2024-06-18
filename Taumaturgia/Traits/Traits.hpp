#pragma once
#include "Concepts/ArmorWearConcepts.hpp"
#include "Concepts/CureHealthConcepts.hpp"
#include "Concepts/DamageConcepts.hpp"
#include "Concepts/HealthConcepts.hpp"
#include "Concepts/NameConcepts.hpp"
#include "Concepts/ProtectionConcepts.hpp"
#include "Concepts/RestoreEffectsConcepts.hpp"

#include "Helpers/trait_accessable.hpp"

#include "NameTraits.hpp"  //

#ifdef WITH_ADD_PROPERTIES
#include "Taumaturgia/User/UserTraits.hpp"
#else
#include "Premade/PremadeTraits.hpp"
#endif
