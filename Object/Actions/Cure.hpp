#pragma once
#include <string>
#include "../Heal.hpp"
#include "../Types/Hp.hpp"

template<typename T>
concept Curable = requires (T x) { x.cureHp; };

template<typename T, bool B = Curable<T>>
struct Cure;

template<typename T>
struct Cure<T, true>: T {
	Cure(const std::string& name, Hp cureHp, auto ...args): T(name, cureHp, std::forward<decltype(args)>(args)...) {}
};

template<typename T>
struct Cure<T, false>: T {
	Cure(const std::string& name, Hp cureHp, auto ...args): T(name, std::forward<decltype(args)>(args)...), cureHp(cureHp) {}

	Hp cureHp{};
};

template<typename T> struct Object::Heal<Cure<T>>: Object::Attack<T>, Object::Defend<T>, Object::Heal<Accept> {
	using Object::Heal<Accept>::operator();
};
