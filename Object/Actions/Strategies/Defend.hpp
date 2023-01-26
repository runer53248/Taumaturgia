#pragma once
#include <iostream>

struct Accept;

template<typename T> struct Defend;
struct Object;

template<template<class> typename T, typename U> struct Defend<T<U>>: Defend<U> {};

template<typename T>
struct Defend {
    bool operator()(T& type, auto... args) {
        return false;
    }

    bool operator()() {
		return false;
	}
};

template<>
struct Defend<Accept> {
	bool operator()(auto& obj, Object* owner, Object* target) {
		std::cout << "(Defend: " << obj.ac << " AC) ";
		return true;
	}

	bool operator()() {
		return true;
	}
};
