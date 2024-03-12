#pragma once
#include <iostream>
#include "../../Object/Concepts/Types/Enums/DurationType.hpp"

constexpr const char* toString(DurationType duration) noexcept {
switch (duration) {
    case DurationType::Day:
        return "Day";
    case DurationType::Hour:
        return "Hour";
    case DurationType::Minute:
        return "Minute";
    case DurationType::Round:
        return "Round";
    case DurationType::Action:
        return "Action";
    case DurationType::Instant:
        return "Instant";
    default:
        return "Unknown";
    }
}

constexpr auto& operator<<(std::ostream& out, DurationType duration) {
    return out << toString(duration);
}
