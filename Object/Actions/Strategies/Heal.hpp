#pragma once
#include <iostream>

struct Accept;

template<typename T> struct Heal;
struct Object;

template<template<class> typename T, typename U> struct Heal<T<U>>: Heal<U> {};

template<typename T>
struct Heal {
    bool operator()(T& type, auto... args) {
        return false;
    }

    bool operator()() {
		return false;
	}
};

template<typename T>
concept Curable = requires (T x) { x.cureHp; };

template<>
struct Heal<Accept> {
	bool operator()(Curable auto& obj, int amount, Object* owner, Object* target) {
		std::cout << "(Healing: " << obj.cureHp <<" of " << amount << ") ";
		return true;
	}

	bool operator()() {
		return true;
	}
};
