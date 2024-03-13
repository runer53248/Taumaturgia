#pragma once
#include <iostream>
#include "Object/Concepts/Types/Duration.hpp"
#include "PrintDurationType.hpp"

constexpr auto& operator<<(std::ostream& out, const Duration& duration) {
    auto value = duration.value();
    if (value == 1) {
        out << " (" << value << " " << duration.type() << ") ";
    } else {
        out << " (" << value << " " << duration.type() << "s) ";
    }
    return out;
}
