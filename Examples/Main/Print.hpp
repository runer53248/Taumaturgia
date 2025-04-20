#pragma once
#include "Examples/PreetyPrint/preety_print.hpp"

// MARK: getOpt_print

void getOpt_print(const Object& obj) {
    std::cout << "get_print_const_ref:\n";
    getOpt<Properties::Health>(obj)  // getOpt as function
        .and_then(print_hp)
        .and_then(print_new_line);
    // getOpt<Properties::Health>(std::as_const(obj))  // getOpt as function with const argument
    //     .and_then(print_hp)
    //     .and_then(print_new_line);
    // obj.getOpt<Properties::Health>()  // getOpt as method
    //     .and_then(print_hp)
    //     .and_then(print_new_line);
    // std::as_const(obj).getOpt<Properties::Health>()  // getOpt as const method
    //     .and_then(print_hp)
    //     .and_then(print_new_line);
    getOpt<Properties::CureHealth>(obj)
        .and_then(print_cure_hp)
        .and_then(print_new_line);
    getOpt<Properties::Protection>(obj)
        .and_then(print_protection)
        .and_then(print_new_line);
    getOpt<Properties::Damage>(obj)
        .and_then(print_dmg)
        .and_then(print_new_line);
    // getOpt<Properties::Damage, const Object>(obj)  // getOpt as function with Object as argument set as const Object
    //     .and_then(print_dmg)
    //     .and_then(print_new_line);
}
