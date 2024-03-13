#pragma once
#include "Examples/PreetyPrint/preety_print.hpp"

void get_print_const_ref(const auto& obj) {
    std::cout << "get_print_const_ref:\n";
    getOpt<Parameter::Health>(obj)
        .and_then(print_hp)
        .and_then(print_new_line);
    getOpt<Parameter::CureHealth>(obj)
        .and_then(print_cure_hp)
        .and_then(print_new_line);
    getOpt<Parameter::Protection>(obj)
        .and_then(print_protection)
        .and_then(print_new_line);
    getOpt<Parameter::Damage>(obj)
        .and_then(print_dmg)
        .and_then(print_new_line);
}

// non-const object will return optional to non-const reference wraper - printing will then show [&]
void get_print_ref(auto& obj) {
    std::cout << "get_print_ref:\n";
    getOpt<Parameter::Health>(obj)
        .and_then(print_hp)
        .and_then(print_new_line);
    getOpt<Parameter::CureHealth>(obj)
        .and_then(print_cure_hp)
        .and_then(print_new_line);
    getOpt<Parameter::Protection>(obj)
        .and_then(print_protection)
        .and_then(print_new_line);
    getOpt<Parameter::Damage>(obj)
        .and_then(print_dmg)
        .and_then(print_new_line);
}

void get_print_with_damage_as_const(auto& obj) {
    std::cout << "get_print_with_damage_as_const:\n";
    getOpt<Parameter::Health>(obj)
        .and_then(print_hp)
        .and_then(print_new_line);
    getOpt<Parameter::CureHealth>(obj)
        .and_then(print_cure_hp)
        .and_then(print_new_line);
    getOpt<Parameter::Protection>(obj)
        .and_then(print_protection)
        .and_then(print_new_line);
    getOpt<Parameter::Damage, const Object>(obj)  // force get version passing const reference
        .and_then(print_dmg)
        .and_then(print_new_line);
    std::cout << '\n';
}
