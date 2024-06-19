#pragma once
#include <iostream>
#include "Usage/Enums/AliveStatus.hpp"

constexpr const char* toString(AliveStatus status) noexcept {
    switch (status) {
    case AliveStatus::Death:
        return "\033[1;31mDeath\033[0m";
    case AliveStatus::Dying:
        return "Dying";
    case AliveStatus::Living:
        return "\033[1;37mLiving\033[0m";
    default:
        return "Unknown";
    }
}

auto& operator<<(std::ostream& out, AliveStatus status) {
    return out << " [" << toString(status) << "] ";
}
