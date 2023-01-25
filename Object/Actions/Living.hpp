#pragma once
#include <string>
#include "../Get.hpp"
#include "../Types/Hp.hpp"

template<typename T>
concept Livable = requires (T x) { x.hp; };

template<typename T, bool B = Livable<T>>
struct Living;

template<typename T>
struct Living<T, true>: T {
	Living(const std::string& name, Hp hp, auto ...args): T(name, hp, std::forward<decltype(args)>(args)...) {}
};

template<typename T>
struct Living<T, false>: T {
	Living(const std::string& name, Hp hp, auto ...args): T(name, std::forward<decltype(args)>(args)...), hp(hp) {}

	Hp hp{};
};

template<typename T> struct Object::Get<Living<T>>: Object::Attack<T>, Object::Defend<T>, Object::Heal<T>, Object::Get<Accept> {
	using Object::Get<Accept>::operator();
};