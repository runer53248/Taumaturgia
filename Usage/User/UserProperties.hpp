#pragma once
#include "Usage/Traits.hpp"

#include "Taumaturgia/Properties/UserProperty.hpp"

#include "Usage/Types/CureHealth/CureHealth.hpp"
#include "Usage/Types/Damage/Damage.hpp"
#include "Usage/Types/EffectTypeContainer/EffectTypeContainer.hpp"
#include "Usage/Types/Health/Health.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "Usage/Types/Protection/Protection.hpp"
#include "Usage/Types/WearContainer/WearContainer.hpp"

template <typename TYPE>
using Living = UserPropertyAdapter<Health>::template type<TYPE>;
template <typename TYPE>
using Wearing = UserPropertyAdapter<WearContainer>::template type<TYPE>;
template <typename TYPE, typename... Tags>
using Damaging = UserPropertyAdapter<Damage, Tags...>::template type<TYPE>;
template <typename TYPE>
using Protecting = UserPropertyAdapter<Protection>::template type<TYPE>;
template <typename TYPE>
using Healing = UserPropertyAdapter<CureHealth>::template type<TYPE>;
template <typename TYPE>
using Restoring = UserPropertyAdapter<EffectTypeContainer>::template type<TYPE>;
template <typename TYPE>
using Naming = UserPropertyAdapter<Name>::template type<TYPE>;

template <typename T>
using Living_impl = impl::UserProperty_<Health, T>;
template <typename T>
using Wearing_impl = impl::UserProperty_<WearContainer, T>;
template <typename T, typename... Tags>
using Damaging_impl = impl::UserProperty_<Damage, T, Tags...>;
template <typename T>
using Protecting_impl = impl::UserProperty_<Protection, T>;
template <typename T>
using Healing_impl = impl::UserProperty_<CureHealth, T>;
template <typename T>
using Restoring_impl = impl::UserProperty_<EffectTypeContainer, T>;
template <typename T>
using Naming_impl = impl::UserProperty_<Name, T>;
