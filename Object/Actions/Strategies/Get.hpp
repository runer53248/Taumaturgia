#pragma once
#include <iostream>
#include <optional>

enum class Parameter {
    Hp
};

struct Accept;

template<typename T> struct Get;
struct Object;

template<template<class> typename T, typename U> struct Get<T<U>>: Get<U> {};

template<typename T>
struct Get {
    std::optional<int*const> operator()(T& type, Parameter param) {
        return {};
    }

    bool operator()() {
		return false;
	}
};

template<>
struct Get<Accept> {
	std::optional<int*const> operator()(auto& obj, Parameter param) {
        if (param == Parameter::Hp){
            std::cout << obj.name << "(HP: " << obj.hp << ")";
            return reinterpret_cast<int*const>(&obj.hp);
        }
        return {};
	}

    bool operator()() {
		return true;
	}
};
