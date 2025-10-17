#pragma once
#include "Taumaturgia/Properties/UserProperty.hpp"
#include "Usage/Traits.hpp"
#include "Usage/Types/Types.hpp"

template <typename TYPE, typename... Tags>
using Living = UserPropertyAdapter<Health, Tags...>::template once<TYPE>;
template <typename TYPE, typename... Tags>
using Wearing = UserPropertyAdapter<WearContainer, Tags...>::template once<TYPE>;
template <typename TYPE, typename... Tags>
using Damaging = UserPropertyAdapter<Damage, Tags...>::template once<TYPE>;
template <typename TYPE, typename... Tags>
using Protecting = UserPropertyAdapter<Protection, Tags...>::template once<TYPE>;
template <typename TYPE, typename... Tags>
using Healing = UserPropertyAdapter<CureHealth, Tags...>::template once<TYPE>;
template <typename TYPE, typename... Tags>
using Restoring = UserPropertyAdapter<EffectTypeContainer, Tags...>::template once<TYPE>;
template <typename TYPE, typename... Tags>
using Naming = UserPropertyAdapter<Name, Tags...>::template once<TYPE>;

template <typename T, typename... Tags>
using Living_impl = impl::UserProperty_<Health, T, Tags...>;
template <typename T, typename... Tags>
using Wearing_impl = impl::UserProperty_<WearContainer, T, Tags...>;
template <typename T, typename... Tags>
using Damaging_impl = impl::UserProperty_<Damage, T, Tags...>;
template <typename T, typename... Tags>
using Protecting_impl = impl::UserProperty_<Protection, T, Tags...>;
template <typename T, typename... Tags>
using Healing_impl = impl::UserProperty_<CureHealth, T, Tags...>;
template <typename T, typename... Tags>
using Restoring_impl = impl::UserProperty_<EffectTypeContainer, T, Tags...>;
template <typename T, typename... Tags>
using Naming_impl = impl::UserProperty_<Name, T, Tags...>;
