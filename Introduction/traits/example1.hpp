#pragma once
#include "Taumaturgia/Traits/Helpers/CustomAccessType.hpp"

class Name;

struct CustomName_1 {  // aggregate with custom Name member
    Name other;
};

template <typename T>
    requires requires(T t) {
        { t.other } -> std::convertible_to<Name&>;
    }
struct traits::CustomAccessType<Name, T> {
    static constexpr decltype(auto) get(auto& el) {
        return (el.other);
    }
};
