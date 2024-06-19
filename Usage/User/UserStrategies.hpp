#pragma once

class Object;
enum class ActionStatus;
enum class AliveStatus : signed char;

#include "Taumaturgia/Strategies/UserStrategy.hpp"

template <typename T>
using AliveStrategy = UserStrategy<Health, T, Livingable<T>, std::optional<AliveStatus>>;
template <typename T>
using AttackStrategy = UserStrategy<Damage, T, Damagingable<T>, ActionStatus, Object*, Object*>;
template <typename T>
using DefendStrategy = UserStrategy<Protection, T, Protectingable<T>, ActionStatus, Object*, Object*>;
template <typename T>
using WearStrategy = UserStrategy<WearContainer, T, Wearingable<T>, ActionStatus, Object*, Object*>;
template <typename T>
using RestoreStrategy = UserStrategy<EffectTypeContainer, T, Restoringable<T>, ActionStatus, Object*, Object*>;
template <typename T>
using HealStrategy = UserStrategy<CureHealth, T, Healingable<T>, ActionStatus, Object*, Object*>;

// forward eventualy implemented strategy
template <typename T>
struct UserStrategy_<Health, Healing_impl<T>, std::optional<AliveStatus>> : public UserStrategy_<Health, T, std::optional<AliveStatus>> {};
template <typename T>
struct UserStrategy_<WearContainer, Wearing_impl<T>, ActionStatus> : public UserStrategy_<WearContainer, T, ActionStatus> {};
template <typename T>
struct UserStrategy_<Damage, Damaging_impl<T>, ActionStatus> : public UserStrategy_<Damage, T, ActionStatus> {};
template <typename T>
struct UserStrategy_<Protection, Protecting_impl<T>, ActionStatus> : public UserStrategy_<Protection, T, ActionStatus> {};
template <typename T>
struct UserStrategy_<CureHealth, Healing_impl<T>, ActionStatus> : public UserStrategy_<CureHealth, T, ActionStatus> {};
template <typename T>
struct UserStrategy_<EffectTypeContainer, Restoring_impl<T>, ActionStatus> : public UserStrategy_<EffectTypeContainer, T, ActionStatus> {};
