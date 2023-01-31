#pragma once
#include <string>
#include "Strategies/Defend.hpp"
#include "../Types/AC.hpp"

namespace {
template <typename T>
struct Protection_: T {
	Protection_(const std::string& name, AC ac, auto ...args): T{name, std::forward<decltype(args)>(args)...}, ac(ac) {}
	Protection_(const std::string& name, auto ...args): T{name, std::forward<decltype(args)>(args)...} {}

	AC ac{};
};
}

template<typename T>
using Protection = std::conditional_t< Protectable<T>, T, Protection_<T> >;

// template<typename T> struct Defend<Protection_<T>>: Defend<Accept> {};
// template<Protectable T> struct Defend<T>: Defend<Accept> {};
