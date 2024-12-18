#pragma once
#include "Examples/PreetyPrint/preety_print.hpp"

// MARK: get_print_const_ref

void get_print_const_ref(const Object& obj) {
    std::cout << "get_print_const_ref:\n";
    obj.getOpt<Properties::Health>()  // getOpt as method
        .and_then(print_hp)
        .and_then(print_new_line);
    std::as_const(obj).getOpt<Properties::CureHealth>()  // getOpt as const method
        .and_then(print_cure_hp)
        .and_then(print_new_line);
    getOpt<Properties::Protection>(obj)  // getOpt as function with Object as argument
        .and_then(print_protection)
        .and_then(print_new_line);
    getOpt<Properties::Damage>(obj)
        .and_then(print_dmg)
        .and_then(print_new_line);
}

// MARK: get_print_ref_with_cure_health_as_const

void get_print_ref_with_cure_health_as_const(type_of<Object> auto& obj) {
    std::cout << "get_print_ref_with_cure_health_as_const:\n";
    // non-const object will return optional to non-const reference wraper
    obj.template getOpt<Properties::Health>()  // getOpt as method
        .and_then(print_hp)
        .and_then(print_new_line);
    std::as_const(obj).template getOpt<Properties::CureHealth>()  // getOpt as const method
        .and_then(print_cure_hp)
        .and_then(print_new_line);
    getOpt<Properties::Protection>(obj)
        .and_then(print_protection)
        .and_then(print_new_line);
    getOpt<Properties::Damage>(obj)
        .and_then(print_dmg)
        .and_then(print_new_line);
}

// MARK: get_print_ref_with_health_and_damage_as_const

void get_print_ref_with_health_and_damage_as_const(auto& obj) {
    std::cout << "get_print_ref_with_health_and_damage_as_const:\n";
    getOpt<Properties::Health>(std::as_const(obj))  // getOpt as function with const Object as argument
        .and_then(print_hp)
        .and_then(print_new_line);
    getOpt<Properties::CureHealth>(obj)
        .and_then(print_cure_hp)
        .and_then(print_new_line);
    getOpt<Properties::Protection>(obj)
        .and_then(print_protection)
        .and_then(print_new_line);
    getOpt<Properties::Damage, const Object>(obj)  // getOpt as function with Object as argument set as const Object
        .and_then(print_dmg)
        .and_then(print_new_line);
    std::cout << '\n';
}
