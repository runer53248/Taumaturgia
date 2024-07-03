#pragma once
#include "Taumaturgia/Strategies/UserStrategy.hpp"

class Object;
enum class ActionStatus;
enum class AliveStatus : signed char;

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

template <typename T>
concept is_custom_alive_strategy = is_custom_type_strategy<Health, T, std::optional<AliveStatus>>;
template <typename T>
concept is_custom_attack_strategy = is_custom_type_strategy<Damage, T, ActionStatus, Object*, Object*>;
template <typename T>
concept is_custom_heal_strategy = is_custom_type_strategy<CureHealth, T, ActionStatus, Object*, Object*>;
template <typename T>
concept is_custom_defend_strategy = is_custom_type_strategy<Protection, T, ActionStatus, Object*, Object*>;
template <typename T>
concept is_custom_restore_strategy = is_custom_type_strategy<EffectTypeContainer, T, ActionStatus, Object*, Object*>;
template <typename T>
concept is_custom_wear_strategy = is_custom_type_strategy<WearContainer, T, ActionStatus, Object*, Object*>;

// forward eventualy implemented strategy
template <typename T>
struct UserStrategy_<Health, Healing_impl<T>> : public UserStrategy_<Health, T> {};
template <typename T>
struct UserStrategy_<WearContainer, Wearing_impl<T>> : public UserStrategy_<WearContainer, T> {};
template <typename T>
struct UserStrategy_<Damage, Damaging_impl<T>> : public UserStrategy_<Damage, T> {};
template <typename T>
struct UserStrategy_<Protection, Protecting_impl<T>> : public UserStrategy_<Protection, T> {};
template <typename T>
struct UserStrategy_<CureHealth, Healing_impl<T>> : public UserStrategy_<CureHealth, T> {};
template <typename T>
struct UserStrategy_<EffectTypeContainer, Restoring_impl<T>> : public UserStrategy_<EffectTypeContainer, T> {};
