#pragma once
#include <string>
#include "../Attack.hpp"
#include "../Types/Damage.hpp"

template<typename T>
concept Damagable = requires (T x) { x.dmg; };

template<typename T, bool B = Damagable<T>>
struct Battle;

template<typename T>
struct Battle<T, true>: T {
	Battle(const std::string& name, Damage dmg, auto ...args): T(name, dmg, std::forward<decltype(args)>(args)...) {}
};

template<typename T>
struct Battle<T, false>: T {
	Battle(const std::string& name, Damage dmg, auto ...args): T(name, std::forward<decltype(args)>(args)...), dmg(dmg) {}

	Damage dmg{};
};

template<typename T> struct Object::Attack<Battle<T>>: Object::Attack<Accept>, Object::Defend<T>, Object::Heal<T> {
	using Object::Attack<Accept>::operator();
};
