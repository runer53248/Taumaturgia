#pragma once
#include <string>
#include "Strategies/Strategies.hpp"
#include "../Types/Hp.hpp"

namespace {
template<typename T>
struct Living_: T {
	Living_(const std::string& name, Hp hp, auto ...args): T(name, std::forward<decltype(args)>(args)...), hp(hp) {}
	Living_(const std::string& name, auto ...args): T(name, std::forward<decltype(args)>(args)...) {}

	Hp hp{};
};
}

template<typename T>
using Living = std::conditional_t< Livable<T>, T, Living_<T> >;

template<typename T> struct Get<Living_<T>>: Attack<T>, Defend<T>, Heal<T>, Get<Accept> {
	using Get<Accept>::operator();
};
