#pragma once
#include <iostream>
#include "Taumaturgia/Types/Enums/BodyLocation.hpp"

constexpr const char* toString(BodyLocation location) noexcept {
    switch (location) {
    case BodyLocation::Head:
        return "\033[1;37mHead\033[0m";
    case BodyLocation::Body:
        return "\033[1;37mBody\033[0m";
    case BodyLocation::Arms:
        return "\033[1;37mArms\033[0m";
    case BodyLocation::Legs:
        return "\033[1;37mLegs\033[0m";
    case BodyLocation::Internal:
        return "\033[1;37mInternal\033[0m";
    case BodyLocation::ALL:
        return "ALL";
    default:
        return "Unknown";
    }
}

auto& operator<<(std::ostream& out, BodyLocation location) {
    return out << toString(location);
}
