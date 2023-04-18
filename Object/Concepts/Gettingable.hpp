#pragma once
#include <type_traits>
#include "Damagingable.hpp"
#include "Healingable.hpp"
#include "Livingable.hpp"
#include "Protectingable.hpp"
#include "Restoringable.hpp"
#include "Wearingable.hpp"

template <typename T>
concept Gettingable = Damagingable<T> or Healingable<T> or Livingable<T> or Protectingable<T> or Restoringable<T> or Wearingable<T>;
