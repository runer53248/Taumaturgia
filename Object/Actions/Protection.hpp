#pragma once
#include <string>
#include "Strategies/Strategies.hpp"
#include "../Types/AC.hpp"

template <typename T>
concept Protectable = requires (T x) { x.ac; };

namespace {
template <typename T>
struct Protection_: T {
	Protection_(const std::string& name, AC ac, auto ...args): T(name, std::forward<decltype(args)>(args)...), ac(ac) {}
	Protection_(const std::string& name, auto ...args): T(name, std::forward<decltype(args)>(args)...){}

	AC ac{};
};
}

template<typename T>
using Protection = std::conditional_t< Protectable<T>, T, Protection_<T> >;

template<typename T> struct Defend<Protection_<T>>: Attack<T>, Defend<Accept>, Heal<T> {
	using Defend<Accept>::operator();
};
