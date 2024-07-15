#pragma once
#include "Usage/Types/PremadeTraits.hpp"

template <typename T>
struct trait_ {};

template <>
struct trait_<Damage> {
    using type = traits::accessDamage;
};

template <>
struct trait_<CureHealth> {
    using type = traits::accessCureHealth;
};

template <>
struct trait_<Health> {
    using type = traits::accessHealth;
};

template <>
struct trait_<Protection> {
    using type = traits::accessProtection;
};

template <>
struct trait_<EffectTypeContainer> {
    using type = traits::accessRestoreEffects;
};

template <>
struct trait_<WearContainer> {
    using type = traits::accessArmorWear;
};

template <>
struct trait_<Name> {
    using type = traits::accessName;
};

template <typename T>
using trait = trait_<T>::type;
