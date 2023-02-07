#pragma once
#include <concepts>
#include "../Concepts/Healingable.hpp"

struct Default;
struct Object;

template <typename T>
struct HealStrategy_ {};

template <template<typename> typename Strategy, typename UserType>
concept HealStrategable = requires (Strategy<UserType> strategy, UserType& type, int amount, Object* owner, Object* target) { 
	{strategy.operator()(type, amount, owner, target)} -> std::same_as<bool>;
};

template <typename T>
using HealStrategy = std::conditional_t<
	Healingable<T>,
	std::conditional_t<
		HealStrategable<HealStrategy_, T>,
		HealStrategy_<T>,
		HealStrategy_<Default> >,
	HealStrategy_<T> >;

template <> struct HealStrategy_<Default> {
    bool operator()(Healingable auto &obj, int amount, Object *owner, Object *target) const;
};
