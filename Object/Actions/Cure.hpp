#pragma once
#include <string>
#include "Strategies/Strategies.hpp"
#include "../Types/Hp.hpp"

namespace {
template<typename T>
struct Cure_: T {
	Cure_(const std::string& name, Hp cureHp, auto ...args): T(name, std::forward<decltype(args)>(args)...), cureHp(cureHp) {}
	Cure_(const std::string& name, auto ...args): T(name, std::forward<decltype(args)>(args)...) {}

	Hp cureHp{};
};
}

template<typename T>
using Cure = std::conditional_t< Curable<T>, T, Cure_<T> >;

template<typename T> struct Heal<Cure_<T>>: Attack<T>, Defend<T>, Heal<Accept> {
	using Heal<Accept>::operator();
};
