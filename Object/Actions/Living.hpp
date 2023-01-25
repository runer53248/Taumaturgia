#pragma once
#include <string>
#include "../Get.hpp"
#include "../Types/Hp.hpp"

template<typename T>
concept Livable = requires (T x) { x.hp; };

namespace {
template<typename T>
struct Living_: T {
	Living_(const std::string& name, Hp hp, auto ...args): T(name, std::forward<decltype(args)>(args)...), hp(hp) {}

	Hp hp{};
};
}

template<typename T>
using Living = std::conditional_t< Livable<T>, T, Living_<T> >;

template<typename T> struct Object::Get<Living_<T>>: Object::Attack<T>, Object::Defend<T>, Object::Heal<T>, Object::Get<Accept> {
	using Object::Get<Accept>::operator();
};
