#pragma once
#include "Object.hpp"

template<typename T, 
        AttackStrategable<T> ATTACK_STRATEGY,
        DefendStrategable<T> DEFEND_STRATEGY,
        HealStrategable<T> HEAL_STRATEGY,
        GetStrategable<T> GET_STRATEGY> 
Object::ObjectModel<T, ATTACK_STRATEGY, DEFEND_STRATEGY, HEAL_STRATEGY, GET_STRATEGY>::ObjectModel(const T& type) : 
    type( type ) {}

template<typename T, 
        AttackStrategable<T> ATTACK_STRATEGY,
        DefendStrategable<T> DEFEND_STRATEGY,
        HealStrategable<T> HEAL_STRATEGY,
        GetStrategable<T> GET_STRATEGY> 
std::string Object::ObjectModel<T, ATTACK_STRATEGY, DEFEND_STRATEGY, HEAL_STRATEGY, GET_STRATEGY>::name() const { 
    return type.name; 
}

template<typename T, 
        AttackStrategable<T> ATTACK_STRATEGY,
        DefendStrategable<T> DEFEND_STRATEGY,
        HealStrategable<T> HEAL_STRATEGY,
        GetStrategable<T> GET_STRATEGY>
bool Object::ObjectModel<T, ATTACK_STRATEGY, DEFEND_STRATEGY, HEAL_STRATEGY, GET_STRATEGY>::attack(Object* owner, Object* target) {
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

template<typename T, 
        AttackStrategable<T> ATTACK_STRATEGY,
        DefendStrategable<T> DEFEND_STRATEGY,
        HealStrategable<T> HEAL_STRATEGY,
        GetStrategable<T> GET_STRATEGY> 
bool Object::ObjectModel<T, ATTACK_STRATEGY, DEFEND_STRATEGY, HEAL_STRATEGY, GET_STRATEGY>::defend(Object* owner, Object* target) {
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

template<typename T, 
        AttackStrategable<T> ATTACK_STRATEGY,
        DefendStrategable<T> DEFEND_STRATEGY,
        HealStrategable<T> HEAL_STRATEGY,
        GetStrategable<T> GET_STRATEGY> 
bool Object::ObjectModel<T, ATTACK_STRATEGY, DEFEND_STRATEGY, HEAL_STRATEGY, GET_STRATEGY>::heal(int amount, Object* owner, Object* target) {
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

template<typename T, 
        AttackStrategable<T> ATTACK_STRATEGY,
        DefendStrategable<T> DEFEND_STRATEGY,
        HealStrategable<T> HEAL_STRATEGY,
        GetStrategable<T> GET_STRATEGY> 
std::optional<int*const> Object::ObjectModel<T, ATTACK_STRATEGY, DEFEND_STRATEGY, HEAL_STRATEGY, GET_STRATEGY>::get(Parameter param) {
    return getFunc(type, param);
}
