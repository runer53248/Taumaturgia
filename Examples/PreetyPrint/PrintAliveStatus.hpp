#pragma once
#include <iostream>
#include "Color_print.hpp"
#include "Usage/Enums/AliveStatus.hpp"

constexpr std::string toString(AliveStatus status) noexcept {
    switch (status) {
    case AliveStatus::Death:
        return Color::Red + "Death" + Color::Reset;
    case AliveStatus::Dying:
        return "Dying";
    case AliveStatus::Living:
        return Color::White + "Living" + Color::Reset;
    default:
        return "Unknown";
    }
}

auto& operator<<(std::ostream& out, AliveStatus status) {
    return out << " [" << toString(status) << "] ";
}
