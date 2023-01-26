#pragma once
#include <string>
#include "Strategies/Strategies.hpp"
#include "../Types/Damage.hpp"

template<typename T>
concept Damagable = requires (T x) { x.dmg; };

namespace {
template<typename T>
struct Battle_: T {
	Battle_(const std::string& name, Damage dmg, auto ...args): T(name, std::forward<decltype(args)>(args)...), dmg(dmg) {}
	Battle_(const std::string& name, auto ...args): T(name, std::forward<decltype(args)>(args)...) {}

	Damage dmg{};
};
}

template<typename T>
using Battle = std::conditional_t< Damagable<T>, T, Battle_<T> >;

template<typename T> struct Attack<Battle_<T>>: Attack<Accept>, Defend<T>, Heal<T> {
	using Attack<Accept>::operator();
};
