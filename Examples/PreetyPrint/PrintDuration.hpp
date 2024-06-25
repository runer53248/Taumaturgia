#pragma once
#include <iostream>
#include "Taumaturgia/Types/Structs/Duration.hpp"
#include "PrintDurationType.hpp"

auto& operator<<(std::ostream& out, const Duration& duration) {
    auto value = duration.value();
    auto type = duration.type();

    if (type == DurationType::Instant) {
        out << "(" << type << "("<<value<<"))";
        return out;
    }
    if (value == 1) {
        out << "(" << value << " " << type << ")";
        return out;
    }
    out << "(" << value << " " << type << "s)";
    return out;
}
