#pragma once
#include "../Object.hpp"

struct Accept;

template<template<class> typename T, typename U> struct Object::Attack<T<U>>: Object::Attack<U> {};

template<typename T>
struct Object::Attack {
    bool operator()(T& type, auto... args) {
        return false;
    }

    bool operator()() {
		return false;
	}
};

template<>
struct Object::Attack<Accept> { // attack specialization
	bool operator()(auto& obj, Object* owner, Object* target) {
		std::cout << "(Attack: " << obj.dmg << " dmg) ";
		return true;
	}

	bool operator()() {
		return true;
	}
};
