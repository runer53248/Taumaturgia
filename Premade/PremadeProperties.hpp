#pragma once
#include "Taumaturgia/Traits/Traits.hpp"

#include "Properties/Damaging.hpp"
#include "Properties/Healing.hpp"
#include "Properties/Living.hpp"
#include "Properties/Naming.hpp"
#include "Properties/Protecting.hpp"
#include "Properties/Restoring.hpp"
#include "Properties/Wearing.hpp"

template <typename T>
using Living_impl = impl::Living_<T>;
template <typename T> 
using Wearing_impl = impl::Wearing_<T>;
template <typename T>
using Damaging_impl = impl::Damaging_<T>;
template <typename T>
using Protecting_impl = impl::Protecting_<T>;
template <typename T>
using Healing_impl = impl::Healing_<T>;
template <typename T>
using Restoring_impl = impl::Restoring_<T>;
