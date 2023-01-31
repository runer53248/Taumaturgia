#pragma once
#include <string>
#include "Strategies/Get.hpp"
#include "../Types/Hp.hpp"

namespace {
template<typename T>
struct Living_: T {
	Living_(const std::string& name, Hp hp, auto ...args): T{name, std::forward<decltype(args)>(args)...}, hp(hp) {}
	Living_(const std::string& name, auto ...args): T{name, std::forward<decltype(args)>(args)...} {}

	Hp hp{};
};
}

template<typename T>
using Living = std::conditional_t< Livable<T>, T, Living_<T> >;

// template<typename T> struct Get<Living_<T>>: Get<Accept> {};
// template<Livable T> struct Get<T>: Get<Accept> {};
