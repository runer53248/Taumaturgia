#pragma once

class Object;
enum class ActionStatus;
enum class AliveStatus : signed char;

#include "Taumaturgia/Strategies/UserStrategy.hpp"

template <typename T>
using AliveStrategy = UserStrategy<Health, T, Livingable<T>, std::optional<AliveStatus>>;
template <typename T>
concept is_alive_strategy = Strategable<AliveStrategy, T, std::optional<AliveStatus>>;

template <typename T>
using AttackStrategy = UserStrategy<Damage, T, Damagingable<T>, ActionStatus, Object*, Object*>;
template <typename T>
concept is_attack_strategy = Strategable<AttackStrategy, T, ActionStatus, Object*, Object*>;

template <typename T>
using DefendStrategy = UserStrategy<Protection, T, Protectingable<T>, ActionStatus, Object*, Object*>;
template <typename T>
concept is_defend_strategy = Strategable<DefendStrategy, T, ActionStatus, Object*, Object*>;

template <typename T>
using WearStrategy = UserStrategy<WearContainer, T, Wearingable<T>, ActionStatus, Object*, Object*>;
template <typename T>
concept is_wear_strategy = Strategable<WearStrategy, T, ActionStatus, Object*, Object*>;

template <typename T>
using RestoreStrategy = UserStrategy<EffectTypeContainer, T, Restoringable<T>, ActionStatus, Object*, Object*>;
template <typename T>
concept is_restore_strategy = Strategable<RestoreStrategy, T, ActionStatus, Object*, Object*>;

template <typename T>
using HealStrategy = UserStrategy<CureHealth, T, Healingable<T>, ActionStatus, Object*, Object*>;
template <typename T>
concept is_heal_strategy = Strategable<HealStrategy, T, ActionStatus, Object*, Object*>;

//

template <typename T>
struct UserStrategy_<Health, Healing_impl<T>, std::optional<AliveStatus>> : public UserStrategy_<Health, T, std::optional<AliveStatus>> {};  // forward eventualy implemented strategy
template <typename T>
struct UserStrategy_<WearContainer, Wearing_impl<T>, ActionStatus> : public UserStrategy_<WearContainer, T, ActionStatus> {};  // forward eventualy implemented strategy
template <typename T>
struct UserStrategy_<Damage, Damaging_impl<T>, ActionStatus> : public UserStrategy_<Damage, T, ActionStatus> {};  // forward eventualy implemented strategy
template <typename T>
struct UserStrategy_<Protection, Protecting_impl<T>, ActionStatus> : public UserStrategy_<Protection, T, ActionStatus> {};  // forward eventualy implemented strategy
template <typename T>
struct UserStrategy_<CureHealth, Healing_impl<T>, ActionStatus> : public UserStrategy_<CureHealth, T, ActionStatus> {};  // forward eventualy implemented strategy
template <typename T>
struct UserStrategy_<EffectTypeContainer, Restoring_impl<T>, ActionStatus> : public UserStrategy_<EffectTypeContainer, T, ActionStatus> {};  // forward eventualy implemented strategy
