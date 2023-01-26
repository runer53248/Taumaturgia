#pragma once
#include <iostream>

struct Accept;

template<typename T> struct Attack;
struct Object;

template<template<class> typename T, typename U> struct Attack<T<U>>: Attack<U> {};

template<typename T>
struct Attack {
    bool operator()(T& type, auto... args) {
        return false;
    }

    bool operator()() {
		return false;
	}
};

template<typename T>
concept Damagable = requires (T x) { x.dmg; };

template<>
struct Attack<Accept> {
	bool operator()(Damagable auto& obj, Object* owner, Object* target) {
		std::cout << "(Attack: " << obj.dmg << " dmg) ";
		return true;
	}

	bool operator()() {
		return true;
	}
};
