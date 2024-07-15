#pragma once
#include "Usage/Types/trait.hpp"

template <typename T>
concept Damagingable = accessable<T, Damage>;
template <typename T>
concept Healingable = accessable<T, CureHealth>;
template <typename T>
concept Livingable = accessable<T, Health>;
template <typename T>
concept Protectingable = accessable<T, Protection>;
template <typename T>
concept Restoringable = accessable<T, EffectTypeContainer>;
template <typename T>
concept Wearingable = accessable<T, WearContainer>;
template <typename T>
concept Namingable = accessable<T, Name>;

template <typename T>
concept Gettingable = Damagingable<T> or
                      Healingable<T> or
                      Livingable<T> or
                      Protectingable<T> or
                      Restoringable<T> or
                      //   Namingable<T> or
                      Wearingable<T>;
