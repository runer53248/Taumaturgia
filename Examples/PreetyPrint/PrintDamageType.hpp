#pragma once
#include <iostream>
#include "../../Object/Concepts/Types/Enums/DamageType.hpp"

constexpr const char* toString(DamageType damageType) noexcept {
    switch (damageType) {
    case DamageType::Physical:
        return "Physical";
    case DamageType::Magical:
        return "Magical";
    case DamageType::Divine:
        return "Divine";
    default:
        return "Unknown";
    }
}

constexpr auto& operator<<(std::ostream& out, DamageType damageType) {
    return out << ' ' << toString(damageType);
}
