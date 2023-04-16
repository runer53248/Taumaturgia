#pragma once
#include <type_traits>
#include "Livingable.hpp"
#include "Healingable.hpp"
#include "Protectingable.hpp"
#include "Damagingable.hpp"
#include "Restoringable.hpp"
#include "Wearingable.hpp"

template <typename T>
concept Gettingable = Damagingable<T> 
	or Healingable<T> 
    or Livingable<T> 
	or Protectingable<T> 
	or Restoringable<T>
	or Wearingable<T>;
