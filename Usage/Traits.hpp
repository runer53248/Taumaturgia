#pragma once
#include "Concepts/ArmorWearConcepts.hpp"
#include "Concepts/CureHealthConcepts.hpp"
#include "Concepts/DamageConcepts.hpp"
#include "Concepts/HealthConcepts.hpp"
#include "Concepts/ProtectionConcepts.hpp"
#include "Concepts/RestoreEffectsConcepts.hpp"

#include "Taumaturgia/Traits/Concepts/NameConcepts.hpp"
#include "Taumaturgia/Traits/Helpers/trait_accessable.hpp"
#include "Taumaturgia/Traits/NameTraits.hpp"  //

#ifdef WITH_ADD_PROPERTIES
#include "Usage/User/UserTraits.hpp"
#else
#include "Usage/Premade/PremadeTraits.hpp"
#endif
