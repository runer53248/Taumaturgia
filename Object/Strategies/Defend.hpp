#pragma once
#include "../Object.hpp"

struct Accept;

template<template<class> typename T, typename U> struct Object::Defend<T<U>>: Object::Defend<U> {};

template<typename T>
struct Object::Defend {
    bool operator()(T& type, auto... args) {
        return false;
    }

    bool operator()() {
		return false;
	}
};

template<>
struct Object::Defend<Accept> { // defend specialization
	bool operator()(auto& obj, Object* owner, Object* target) {
		std::cout << "(Defend: " << obj.ac << " AC) ";
		return true;
	}

	bool operator()() {
		return true;
	}
};
