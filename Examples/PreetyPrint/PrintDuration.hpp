#pragma once
#include <iostream>
#include "../../Object/Concepts/Types/Duration.hpp"
#include "PrintDurationType.hpp"

auto& operator<<(std::ostream& out, Duration duration) {
    auto value = duration.value();
    if (value == 1) {
        out << " (" << value << " " << duration.type() << ") ";
    } else {
        out << " (" << value << " " << duration.type() << "s) ";
    }
    
    return out;
}
