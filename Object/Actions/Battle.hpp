#pragma once
#include <string>
#include "../Attack.hpp"
#include "../Types/Damage.hpp"

template<typename T>
concept Damagable = requires (T x) { x.dmg; };

namespace {
template<typename T>
struct Battle_: T {
	Battle_(const std::string& name, Damage dmg, auto ...args): T(name, std::forward<decltype(args)>(args)...), dmg(dmg) {}

	Damage dmg{};
};
}

template<typename T>
using Battle = std::conditional_t< Damagable<T>, T, Battle_<T> >;

template<typename T> struct Object::Attack<Battle_<T>>: Object::Attack<Accept>, Object::Defend<T>, Object::Heal<T> {
	using Object::Attack<Accept>::operator();
};
