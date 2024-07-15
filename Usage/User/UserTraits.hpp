#pragma once
#include "Taumaturgia/Traits/UserTypeTraits.hpp"
#include "Usage/Types/Concepts.hpp"

template <typename T>
struct trait_ {};

template <>
struct trait_<Damage> {
    using type = traits::accessType<Damage>;
};

template <>
struct trait_<CureHealth> {
    using type = traits::accessType<CureHealth>;
};

template <>
struct trait_<Health> {
    using type = traits::accessType<Health>;
};

template <>
struct trait_<Protection> {
    using type = traits::accessType<Protection>;
};

template <>
struct trait_<EffectTypeContainer> {
    using type = traits::accessType<EffectTypeContainer>;
};

template <>
struct trait_<WearContainer> {
    using type = traits::accessType<WearContainer>;
};

template <>
struct trait_<Name> {
    using type = traits::accessType<Name, std::string>;
};

template <typename T>
using trait = trait_<T>::type;
