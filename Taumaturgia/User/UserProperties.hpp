#pragma once
#include "Taumaturgia/Properties/UserProperty.hpp"

#include "Taumaturgia/Traits/Traits.hpp"

#include "Taumaturgia/Types/Name.hpp"
#include "Taumaturgia/Types/Health.hpp"
#include "Taumaturgia/Types/WearContainer.hpp"
#include "Taumaturgia/Types/Damage.hpp"
#include "Taumaturgia/Types/CureHealth.hpp"
#include "Taumaturgia/Types/Protection.hpp"

template <typename TYPE>
using Living = UserPropertyConceptAdapter<Health, Livingable<TYPE>>::template type<TYPE>;
template <typename TYPE>
using Wearing = UserPropertyConceptAdapter<WearContainer, Wearingable<TYPE>>::template type<TYPE>;
template <typename TYPE>
using Damaging = UserPropertyConceptAdapter<Damage, Damagingable<TYPE>>::template type<TYPE>;
template <typename TYPE>
using Protecting = UserPropertyConceptAdapter<Protection, Protectingable<TYPE>>::template type<TYPE>;
template <typename TYPE>
using Healing = UserPropertyConceptAdapter<CureHealth, Healingable<TYPE>>::template type<TYPE>;
template <typename TYPE>
using Restoring = UserPropertyConceptAdapter<EffectTypeContainer, Restoringable<TYPE>>::template type<TYPE>;
template <typename TYPE>
using Naming = UserPropertyConceptAdapter<Name, Namingable<TYPE>>::template type<TYPE>;

template <typename T>
using Living_impl = impl::UserProperty_<Health, T>;
template <typename T> 
using Wearing_impl = impl::UserProperty_<WearContainer, T>;
template <typename T>
using Damaging_impl = impl::UserProperty_<Damage, T>;
template <typename T>
using Protecting_impl = impl::UserProperty_<Protection, T>;
template <typename T>
using Healing_impl = impl::UserProperty_<CureHealth, T>;
template <typename T>
using Restoring_impl = impl::UserProperty_<EffectTypeContainer, T>;
