#pragma once
#include "../Object.hpp"

struct Accept;

template<template<class> typename T, typename U> struct Object::Get<T<U>>: Object::Get<U> {};

template<typename T>
struct Object::Get {
    std::optional<int*const> operator()(T& type, Parameter param) {
        return {};
    }

    bool operator()() {
		return false;
	}
};

template<>
struct Object::Get<Accept> { // get specialization
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
