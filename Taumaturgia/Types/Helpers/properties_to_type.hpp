#pragma once
#include "Taumaturgia/Types/Enums/Properties.hpp"

struct Health;
struct CureHealth;
struct Damage;
struct Protection;
struct EffectTypeContainer;
struct WearContainer;

namespace impl {

template <Properties P>
struct properties_to_type;

template <>
struct properties_to_type<Properties::Health> {
    using type = Health;
};

template <>
struct properties_to_type<Properties::CureHealth> {
    using type = CureHealth;
};

template <>
struct properties_to_type<Properties::Damage> {
    using type = Damage;
};

template <>
struct properties_to_type<Properties::Protection> {
    using type = Protection;
};

template <>
struct properties_to_type<Properties::Restore> {
    using type = EffectTypeContainer;
};
template <>
struct properties_to_type<Properties::Wear> {
    using type = WearContainer;
};

}  // namespace impl

template <Properties PROPERTY>
using properties_to_type = impl::properties_to_type<PROPERTY>::type;
