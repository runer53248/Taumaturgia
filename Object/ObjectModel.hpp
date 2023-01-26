#pragma once
#include "Object.hpp"

template<Nameable T> 
std::string Object::ObjectModel<T>::name() const { 
    return type.name; 
}

template<Nameable T>
bool Object::ObjectModel<T>::attack(Object* owner, Object* target) {
    if (not attackFunc()) {
        return false;
    }
    if (not owner) {
        return false;
    }
    if (not owner->get(Parameter::Hp)){
        std::cout << owner->name();
    }
    std::cout << " " << "attack ";
    if (not attackFunc(type, owner, target)) {
        std::cout << "and misses\n";
        return false;
    }
    bool self = false;
    if ((owner == target) or not target) {
        std::cout << "self";
        self = true;
    }

    if (not self) {
        if (not target->get(Parameter::Hp)){
            std::cout << target->name();
        }
    }

    std::cout << " with " << name() << "\n";
    return true;
}

template<Nameable T> 
bool Object::ObjectModel<T>::defend(Object* owner, Object* target) {
    if (not defendFunc()) {
        return false;
    }
    if (not owner) {
        return false;
    }
    if (not owner->get(Parameter::Hp)){
        std::cout << owner->name();
    }
    std::cout << " " << "defend ";
    if (not defendFunc(type, owner, target)) {
        std::cout << "and misses\n";
        return false;
    }
    bool self = false;
    if ((owner == target) or not target) {
        std::cout << "self";
        self = true;
    }

    if (not self) {
        std::cout << target->name();
    }

    std::cout << " with " << name() << "\n";
    return true;
}

template<Nameable T> 
bool Object::ObjectModel<T>::heal(int amount, Object* owner, Object* target) {
    if (not healFunc()) {
        return false;
    }
    if (not owner) {
        return false;
    }
    if (not owner->get(Parameter::Hp)){
        std::cout << owner->name();
    }
    std::cout << " " << "heal ";
    if (not healFunc(type, amount, owner, target)) {
        std::cout << "and misses\n";
        return false;
    }
    bool self = false;
    if ((owner == target) or not target) {
        std::cout << "self";
        self = true;
    }

    if (not self) {
        std::cout << target->name();
    }
    std::cout << " with " << name() << "\n";
    return true;
}

template<Nameable T> 
std::optional<int*const> Object::ObjectModel<T>::get(Parameter param) {
    return getFunc(type, param);
}
