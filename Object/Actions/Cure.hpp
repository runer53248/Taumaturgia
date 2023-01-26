#pragma once
#include <string>
#include "../Strategies/Heal.hpp"
#include "../Types/Hp.hpp"

template<typename T>
concept Curable = requires (T x) { x.cureHp; };

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

template<typename T> struct Object::Heal<Cure_<T>>: Object::Attack<T>, Object::Defend<T>, Object::Heal<Accept> {
	using Object::Heal<Accept>::operator();
};
