#pragma once
#include <iostream>
#include "Taumaturgia/Types/Enums/DamageType.hpp"

constexpr const char* toString(DamageType damageType) noexcept {
    switch (damageType) {
    case DamageType::Physical:
        return "\033[1;37mPhysical\033[0m";
    case DamageType::Magical:
        return "\033[1;34mMagical\033[0m";
    case DamageType::Divine:
        return "\033[1;33mDivine\033[0m";
    default:
        return "Unknown";
    }
}

auto& operator<<(std::ostream& out, DamageType damageType) {
    return out << toString(damageType);
}
