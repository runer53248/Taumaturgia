#pragma once

void get_print_const_ref(const auto& obj) {
    std::cout << "get and print const reference:\n";
    [](const auto& obj) {  // get version passing const reference
        getOpt<Parameter::Health>(obj)
            .and_then(print_hp);
        std::cout << '\n';
        getOpt<Parameter::CureHealth>(obj)
            .and_then(print_cure_hp);
        std::cout << '\n';
        // getOpt<Parameter::Protection>(obj)
        //    .and_then(print_protection); // ignored - object dont have Ac
        // std::cout << '\n';
        getOpt<Parameter::Damage>(obj)
            .and_then(print_dmg);
        std::cout << '\n';
    }(obj);
}

void get_print_ref(auto& obj) {
    std::cout << "get and print reference:\n";  // non-const object will return optional to non-const reference wraper - printing will then show [&]
    [](auto& obj) {                             // get version passing reference
        getOpt<Parameter::Health>(obj)
            .and_then(print_hp);
        std::cout << '\n';
        getOpt<Parameter::CureHealth>(obj)
            .and_then(print_cure_hp);
        std::cout << '\n';
        // getOpt<Parameter::Protection>(obj).and_then(print_protection); // ignored - object dont have Ac
        // std::cout << '\n';
        getOpt<Parameter::Damage>(obj)
            .and_then(print_dmg);
        std::cout << '\n';
    }(obj);
}

void get_print(auto& obj) {
    std::cout << "get and print:\n";
    getOpt<Parameter::Health>(obj)
        .and_then(print_hp);  // get version passing reference
    std::cout << '\n';
    getOpt<Parameter::CureHealth>(obj)
        .and_then(print_cure_hp);
    std::cout << '\n';
    // getOpt<Parameter::Protection>(gustav_obj).and_then(print_protection); // ignored - object dont have Ac
    // std::cout << '\n';
    std::cout << "get and print - forced to return const reference:\n";
    getOpt<Parameter::Damage, const Object>(obj)
        .and_then(print_dmg);  // force get version passing const reference
    std::cout << '\n';
    std::cout << '\n';
}
