#pragma once
#include "Taumaturgia/Properties/UserProperty.hpp"

#include "Usage/Types/CureHealth/CureHealth.hpp"
#include "Usage/Types/Damage/Damage.hpp"
#include "Usage/Types/EffectTypeContainer/EffectTypeContainer.hpp"
#include "Usage/Types/Health/Health.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "Usage/Types/Protection/Protection.hpp"
#include "Usage/Types/WearContainer/WearContainer.hpp"

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
template <typename T>
using Naming_impl = impl::UserProperty_<Name, T>;
