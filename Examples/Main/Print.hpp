#pragma once
#include "Examples/PreetyPrint/preety_print.hpp"

// MARK: get_print_const_ref

void get_print_const_ref(const Object& obj) {
    std::cout << "get_print_const_ref:\n";
    obj.getOpt<Parameter::Health>()  // getOpt as method
        .and_then(print_hp)
        .and_then(print_new_line);
    std::as_const(obj).getOpt<Parameter::CureHealth>()  // getOpt as const method
        .and_then(print_cure_hp)
        .and_then(print_new_line);
    getOpt<Parameter::Protection>(obj)  // getOpt as function with Object as argument
        .and_then(print_protection)
        .and_then(print_new_line);
    getOpt<Parameter::Damage>(obj)
        .and_then(print_dmg)
        .and_then(print_new_line);
}

// MARK: get_print_ref

// non-const object will return optional to non-const reference wraper - printing will then show [&]
void get_print_ref(is_object auto& obj) {
    std::cout << "get_print_ref:\n";
    obj.template getOpt<Parameter::Health>()  // getOpt as method
        .and_then(print_hp)
        .and_then(print_new_line);
    std::as_const(obj).template getOpt<Parameter::CureHealth>()  // getOpt as const method
        .and_then(print_cure_hp)
        .and_then(print_new_line);
    getOpt<Parameter::Protection>(obj)
        .and_then(print_protection)
        .and_then(print_new_line);
    getOpt<Parameter::Damage>(obj)
        .and_then(print_dmg)
        .and_then(print_new_line);
}

// MARK: get_print_with_damage_as_const

void get_print_with_damage_as_const(auto& obj) {
    std::cout << "get_print_with_damage_as_const:\n";
    getOpt<Parameter::Health>(std::as_const(obj))  // getOpt as function with const Object as argument
        .and_then(print_hp)
        .and_then(print_new_line);
    getOpt<Parameter::CureHealth>(obj)
        .and_then(print_cure_hp)
        .and_then(print_new_line);
    getOpt<Parameter::Protection>(obj)
        .and_then(print_protection)
        .and_then(print_new_line);
    getOpt<Parameter::Damage, const Object>(obj)  // getOpt as function with Object as argument set as const Object
        .and_then(print_dmg)
        .and_then(print_new_line);
    std::cout << '\n';
}
