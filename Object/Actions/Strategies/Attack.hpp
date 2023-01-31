#pragma once
#include <iostream>

struct Accept;
struct Object;

template<typename T>
concept Damagable = requires (T x) { x.dmg; };

namespace {
template<typename T>
struct Attack_ {
    bool operator()(T& type, auto... args) {
        return false;
    }

    bool operator()() {
		return false;
	}
};

template<>
struct Attack_<Accept> {
	bool operator()(Damagable auto& obj, Object* owner, Object* target) {
		std::cout << "(Attack: " << obj.dmg << " dmg) ";
		return true;
	}

	bool operator()() {
		return true;
	}
};
}

template<typename T>
using AttackStrategy = std::conditional_t< 
	Damagable<T>, // is type damagable
	Attack_<Accept>, // default strategy
	Attack_<T> >; // not damagable
