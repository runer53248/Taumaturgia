#pragma once
#include <iostream>
#include "PrintDurationType.hpp"
#include "Usage/Types/Structs/Duration.hpp"

auto& operator<<(std::ostream& out, const Duration& duration) {
    auto value = duration.value();
    auto type = duration.type();

    if (type == DurationType::Instant) {
        if (value == 0) {
            out << "(" << type << ")";
        } else {
            out << "(" << type << "(" << value << "))";
        }
        return out;
    }
    if (value == 1) {
        out << "(" << value << " " << type << ")";
        return out;
    }
    out << "(" << value << " " << type << "s)";
    return out;
}
