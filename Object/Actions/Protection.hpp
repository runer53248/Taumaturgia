#pragma once
#include <string>
#include "../Defend.hpp"
#include "../Types/AC.hpp"

template <typename T>
concept Protectable = requires (T x) { x.ac; };

template<typename T, bool B = Protectable<T>>
struct Protection;

template <typename T>
struct Protection<T, true>: T {
	Protection(const std::string& name, AC ac, auto ...args): T(name, ac, std::forward<decltype(args)>(args)...) {}
};

template <typename T>
struct Protection<T, false>: T {
	Protection(const std::string& name, AC ac, auto ...args): T(name, std::forward<decltype(args)>(args)...), ac(ac) {}

	AC ac{};
};

template<typename T> struct Object::Defend<Protection<T>>: Object::Attack<T>, Object::Defend<Accept>, Object::Heal<T> {
	using Object::Defend<Accept>::operator();
};
