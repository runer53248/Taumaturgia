#pragma once
#include "../Concepts/Namingable.hpp"
#include "../Strategies/WearStrategy.hpp"

template <typename T>
struct Wearing_: T {
	Wearing_(const Name& name, ArmorClassContainer armorWear, auto ...args): T{name, std::forward<decltype(args)>(args)...}, armorWear(armorWear) {}
	Wearing_(const Name& name, auto ...args): T{name, std::forward<decltype(args)>(args)...} {}

	ArmorClassContainer armorWear{};
};

struct Wearing_Test{};
static_assert(Wearingable< Wearing_<Wearing_Test> >);

template <typename T>
using Wearing = std::conditional_t< Wearingable<T>, T, Wearing_<T> >;

template <typename T>
struct WearStrategy_<Wearing_<T>> : WearStrategy_<T> {}; // forward eventualy implemented strategy
