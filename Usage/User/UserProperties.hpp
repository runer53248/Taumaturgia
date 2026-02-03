#pragma once
#include "Taumaturgia/Properties/UserProperty.hpp"
#include "Usage/Traits.hpp"
#include "Usage/Types/Types.hpp"

template <typename TYPE, isTag TAGS = no_tag>
using Living = UserPropertyAdapter<Health, TAGS>::template once<TYPE>;
template <typename TYPE, isTag TAGS = no_tag>
using Wearing = UserPropertyAdapter<WearContainer, TAGS>::template once<TYPE>;
template <typename TYPE, isTag TAGS = no_tag>
using Damaging = UserPropertyAdapter<Damage, TAGS>::template once<TYPE>;
template <typename TYPE, isTag TAGS = no_tag>
using Protecting = UserPropertyAdapter<Protection, TAGS>::template once<TYPE>;
template <typename TYPE, isTag TAGS = no_tag>
using Healing = UserPropertyAdapter<CureHealth, TAGS>::template once<TYPE>;
template <typename TYPE, isTag TAGS = no_tag>
using Restoring = UserPropertyAdapter<EffectTypeContainer, TAGS>::template once<TYPE>;
template <typename TYPE, isTag TAGS = no_tag>
using Naming = UserPropertyAdapter<Name, TAGS>::template once<TYPE>;

template <typename T, isTag TAGS = no_tag>
using Living_impl = impl::UserProperty_<Health, T, TAGS>;
template <typename T, isTag TAGS = no_tag>
using Wearing_impl = impl::UserProperty_<WearContainer, T, TAGS>;
template <typename T, isTag TAGS = no_tag>
using Damaging_impl = impl::UserProperty_<Damage, T, TAGS>;
template <typename T, isTag TAGS = no_tag>
using Protecting_impl = impl::UserProperty_<Protection, T, TAGS>;
template <typename T, isTag TAGS = no_tag>
using Healing_impl = impl::UserProperty_<CureHealth, T, TAGS>;
template <typename T, isTag TAGS = no_tag>
using Restoring_impl = impl::UserProperty_<EffectTypeContainer, T, TAGS>;
template <typename T, isTag TAGS = no_tag>
using Naming_impl = impl::UserProperty_<Name, T, TAGS>;
