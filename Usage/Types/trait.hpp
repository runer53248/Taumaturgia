#pragma once
#include "CureHealth/accessCureHealth.hpp"
#include "Damage/accessDamage.hpp"
#include "EffectTypeContainer/accessRestoreEffects.hpp"
#include "Health/accessHealth.hpp"
#include "Name/accessName.hpp"
#include "Protection/accessProtection.hpp"
#include "WearContainer/accessArmorWear.hpp"

template <typename T>
struct trait_ {
    struct Default {
        template <typename>
        static constexpr bool accessable = false;
    };
    using type = Default;
};

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

template <typename T, typename TYPE>
concept accessable = trait<TYPE>::template accessable<T>;
