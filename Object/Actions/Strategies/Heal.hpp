#pragma once
#include <iostream>

struct Accept;
struct Object;

template<typename T>
concept Curable = requires (T x) { x.cureHp; };

namespace {
template<typename T>
struct Heal_ {
    bool operator()(T& type, auto... args) {
        return false;
    }

    bool operator()() {
		return false;
	}
};

template<>
struct Heal_<Accept> {
	bool operator()(Curable auto& obj, int amount, Object* owner, Object* target) {
		std::cout << "(Healing: " << obj.cureHp <<" of " << amount << ") ";
		return true;
	}

	bool operator()() {
		return true;
	}
};
}

template<typename T>
using HealStrategy = std::conditional_t< Curable<T>, Heal_<Accept>, Heal_<T> >;
