#pragma once
#include <iostream>
#include <optional>

enum class Parameter {
    Hp
};

struct Accept;
struct Object;

template<typename T>
concept Livable = requires (T x) { x.hp; };

namespace {
template<typename T>
struct Get_ {
    std::optional<int*const> operator()(T& type, Parameter param) {
        return {};
    }

    bool operator()() {
		return false;
	}
};

template<>
struct Get_<Accept> {
	std::optional<int*const> operator()(Livable auto& obj, Parameter param) {
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
}

template<typename T>
using GetStrategy = std::conditional_t< 
	Livable<T>, // is type Livable
	Get_<Accept>, // default strategy
	Get_<T> >; // not Livable