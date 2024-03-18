#pragma once
#include <iostream>
#include <string>

template <char Open, char Close>
auto& print_in_braces(std::ostream& out, std::string_view name, auto&& func) {
    std::cout << Open << name << ": ";
    func();
    std::cout << Close;
    return out;
};

template <typename Func>
auto& print_in_round_braces(std::ostream& out, std::string_view name, Func&& func) {
    return print_in_braces<'(', ')'>(out, name, std::forward<Func>(func));
}

template <typename Func>
auto& print_in_curly_braces(std::ostream& out, std::string_view name, Func&& func) {
    return print_in_braces<'{', '}'>(out, name, std::forward<Func>(func));
}
