#pragma once
#include "Usage/Types/access_traits.hpp"

template <typename T>
concept Damagingable = trait_accessable<T, Damage>;
template <typename T>
concept Healingable = trait_accessable<T, CureHealth>;
template <typename T>
concept Livingable = trait_accessable<T, Health>;
template <typename T>
concept Protectingable = trait_accessable<T, Protection>;
template <typename T>
concept Restoringable = trait_accessable<T, EffectTypeContainer>;
template <typename T>
concept Wearingable = trait_accessable<T, WearContainer>;
template <typename T>
concept Namingable = trait_accessable<T, Name>;

template <typename T>
concept Gettingable = Damagingable<T> or
                      Healingable<T> or
                      Livingable<T> or
                      Protectingable<T> or
                      Restoringable<T> or
                      //   Namingable<T> or
                      Wearingable<T>;
