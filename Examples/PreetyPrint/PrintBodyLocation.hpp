#pragma once
#include <iostream>
#include "../../Object/Concepts/Types/Enums/BodyLocation.hpp"

constexpr const char* toString(BodyLocation location) noexcept {
    switch (location) {
    case BodyLocation::Head:
        return "Head";
    case BodyLocation::Body:
        return "Body";
    case BodyLocation::Arms:
        return "Arms";
    case BodyLocation::Legs:
        return "Legs";
    case BodyLocation::Internal:
        return "Internal";
    case BodyLocation::ALL:
        return "ALL";
    default:
        return "Unknown";
    }
}

constexpr auto& operator<<(std::ostream& out, BodyLocation location) {
    return out << toString(location);
}
