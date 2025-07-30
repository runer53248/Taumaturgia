#pragma once
#include <iostream>
#include "Color_print.hpp"
#include "Usage/Enums/DamageType.hpp"

constexpr std::string toString(DamageType damageType) noexcept {
    switch (damageType) {
    case DamageType::Physical:
        return Color::White + "Physical" + Color::Reset;
    case DamageType::Magical:
        return Color::Yellow + "Magical" + Color::Reset;
    case DamageType::Divine:
        return Color::Blue + "Divine" + Color::Reset;
    default:
        return "Unknown";
    }
}

auto& operator<<(std::ostream& out, DamageType damageType) {
    return out << toString(damageType);
}
