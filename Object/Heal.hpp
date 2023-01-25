#pragma once
#include "Object.hpp"

struct Accept;

template<template<class> typename T, typename U> struct Object::Heal<T<U>>: Object::Heal<U> {};

template<typename T>
struct Object::Heal {
    bool operator()(T& type, auto... args) {
        return false;
    }

    bool operator()() {
		return false;
	}
};

template<> struct Object::Heal<Accept> { // heal specialization
	bool operator()(auto& obj, int amount, Object* owner, Object* target) {
		std::cout << "(Healing: " << obj.cureHp <<" of " << amount << ") ";
		return true;
	}

	bool operator()() {
		return true;
	}
};
