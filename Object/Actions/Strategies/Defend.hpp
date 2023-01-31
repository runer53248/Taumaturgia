#pragma once
#include <iostream>

struct Accept;
struct Object;

template <typename T>
concept Protectable = requires (T x) { x.ac; };

namespace {
template<typename T>
struct Defend_ {
    bool operator()(T& type, auto... args) {
        return false;
    }

    bool operator()() {
		return false;
	}
};

template<>
struct Defend_<Accept> {
	bool operator()(Protectable auto& obj, Object* owner, Object* target) {
		std::cout << "(Defend: " << obj.ac << " AC) ";
		return true;
	}

	bool operator()() {
		return true;
	}
};
}

template<typename T>
using DefendStrategy = std::conditional_t< 
	Protectable<T>, // is type Protectable
	Defend_<Accept>, // default strategy
	Defend_<T> >; // not Protectable
