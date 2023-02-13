#pragma once
#include <concepts>
#include "../Concepts/Healingable.hpp"

struct Default;
struct Object;

template <typename T>
struct HealStrategy_ {};

template <template<typename> typename Strategy, typename UserType>
concept HealStrategable = requires (Strategy<UserType> strategy, UserType& type, Object* owner, Object* target) { 
	{strategy.operator()(type, owner, target)} -> std::same_as<bool>;
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
    bool operator()(Healingable auto &obj, Object *owner, Object *target) const;
};
