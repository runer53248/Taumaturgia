#pragma once
#ifdef WITH_ADD_PROPERTIES
#include "Usage/User/UserTraits.hpp"
#else
#include "Usage/Premade/PremadeTraits.hpp"
#endif

template <typename T>
concept Damagingable = trait<Damage>::accessable<T>;
template <typename T>
concept Healingable = trait<CureHealth>::accessable<T>;
template <typename T>
concept Livingable = trait<Health>::accessable<T>;
template <typename T>
concept Protectingable = trait<Protection>::accessable<T>;
template <typename T>
concept Restoringable = trait<EffectTypeContainer>::accessable<T>;
template <typename T>
concept Wearingable = trait<WearContainer>::accessable<T>;
template <typename T>
concept Namingable = trait<Name>::accessable<T>;

template <typename T>
concept Gettingable = Damagingable<T> or
                      Healingable<T> or
                      Livingable<T> or
                      Protectingable<T> or
                      Restoringable<T> or
                    //   Namingable<T> or
                      Wearingable<T>;
