#pragma once
#include <iostream>
#include "../../Object/Enums/AliveStatus.hpp"

constexpr const char* toString(AliveStatus status) noexcept {
    switch (status) {
    case AliveStatus::Death:
        return "Death";
    case AliveStatus::Dying:
        return "Dying";
    case AliveStatus::Living:
        return "Living";
    default:
        return "Unknown";
    }
}

constexpr auto& operator<<(std::ostream& out, AliveStatus status) {
    return out << " [" << toString(status) << "] ";
}
