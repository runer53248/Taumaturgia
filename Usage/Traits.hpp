#pragma once
#ifdef WITH_ADD_PROPERTIES
#include "Usage/User/UserTraits.hpp"
#else
#include "Usage/Premade/PremadeTraits.hpp"
#endif

template <typename T>
concept Damagingable = Damagingable_trait::accessable<T>;
template <typename T>
concept Healingable = Healingable_trait::accessable<T>;
template <typename T>
concept Livingable = Livingable_trait::accessable<T>;
template <typename T>
concept Protectingable = Protectingable_trait::accessable<T>;
template <typename T>
concept Restoringable = Restoringable_trait::accessable<T>;
template <typename T>
concept Wearingable = Wearingable_trait::accessable<T>;
template <typename T>
concept Namingable = Namingable_trait::accessable<T>;

template <typename T>
concept Gettingable = Damagingable<T> or
                      Healingable<T> or
                      Livingable<T> or
                      Protectingable<T> or
                      Restoringable<T> or
                    //   Namingable<T> or
                      Wearingable<T>;
