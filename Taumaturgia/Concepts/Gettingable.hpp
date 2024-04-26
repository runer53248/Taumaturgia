#pragma once
#include "Taumaturgia/Traits/CureHealthTraits.hpp"
#include "Taumaturgia/Traits/DamageTraits.hpp"
#include "Taumaturgia/Traits/ArmorWearTraits.hpp"
#include "Taumaturgia/Traits/HealthTraits.hpp"
#include "Taumaturgia/Traits/ProtectionTraits.hpp"
#include "Taumaturgia/Traits/RestoreEffectsTraits.hpp"

template <typename T>
concept Gettingable = Damagingable<T> or Healingable<T> or Livingable<T> or Protectingable<T> or Restoringable<T> or Wearingable<T>;
