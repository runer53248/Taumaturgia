#pragma once
#include <iostream>
#include "Usage/Enums/BodyLocation.hpp"
#include "Color_print.hpp"

constexpr std::string toString(BodyLocation location) noexcept {
    switch (location) {
    case BodyLocation::Head:
        return Color::White + "Head" + Color::Reset;
    case BodyLocation::Body:
        return Color::White + "Body" + Color::Reset;
    case BodyLocation::Arms:
        return Color::White + "Arms" + Color::Reset;
    case BodyLocation::Legs:
        return Color::White + "Legs" + Color::Reset;
    case BodyLocation::Internal:
        return Color::White + "Internal" + Color::Reset;
    case BodyLocation::ALL:
        return "ALL";
    default:
        return "Unknown";
    }
}

auto& operator<<(std::ostream& out, BodyLocation location) {
    return out << toString(location);
}
