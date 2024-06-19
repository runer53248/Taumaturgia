#pragma once
#include "Strategies/AliveStrategy.hpp"
#include "Strategies/AttackStrategy.hpp"
#include "Strategies/DefendStrategy.hpp"
#include "Strategies/HealStrategy.hpp"
#include "Strategies/RestoreStrategy.hpp"
#include "Strategies/WearStrategy.hpp"
#include "Usage/Traits.hpp"

// forward eventualy implemented strategy
template <typename T>
struct AliveStrategy_<Living_impl<T>> : public AliveStrategy_<T> {};
template <typename T>
struct WearStrategy_<Wearing_impl<T>> : public WearStrategy_<T> {};
template <typename T>
struct AttackStrategy_<Damaging_impl<T>> : public AttackStrategy_<T> {};
template <typename T>
struct DefendStrategy_<Protecting_impl<T>> : public DefendStrategy_<T> {};
template <typename T>
struct HealStrategy_<Healing_impl<T>> : public HealStrategy_<T> {};
template <typename T>
struct RestoreStrategy_<Restoring_impl<T>> : public RestoreStrategy_<T> {};
