#pragma once
#ifdef WITH_ADD_PROPERTIES
#include "Usage/User/UserTraits.hpp"
#else
#include "Usage/Premade/PremadeTraits.hpp"
#endif

template <typename T>
concept Damagingable = traits::helpers::trait_accessable<T, Damagingable_trait, Damage>;
template <typename T>
concept Healingable = traits::helpers::trait_accessable<T, Healingable_trait, CureHealth>;
template <typename T>
concept Livingable = traits::helpers::trait_accessable<T, Livingable_trait, Health>;
template <typename T>
concept Protectingable = traits::helpers::trait_accessable<T, Protectingable_trait, Protection>;
template <typename T>
concept Restoringable = traits::helpers::trait_accessable<T, Restoringable_trait, EffectTypeContainer>;
template <typename T>
concept Wearingable = traits::helpers::trait_accessable<T, Wearingable_trait, WearContainer>;
template <typename T>
concept Namingable = traits::helpers::trait_access_covertable<T, Namingable_trait, std::string>;
template <typename T>
concept Gettingable = Damagingable<T> or
                      Healingable<T> or
                      Livingable<T> or
                      Protectingable<T> or
                      Restoringable<T> or
                      Wearingable<T>;
