#pragma once
#include <iostream>
#include "../../Object/Concepts/Types/CureHealth.hpp"

constexpr const char* toString(CureValueType type) noexcept {
    switch (type) {
    case CureValueType::VALUE:
        return " points";
    case CureValueType::CURRENT_PERCENT:
        return " %%";
    case CureValueType::MAX_PERCENT:
        return " %";
    default:
        return " Unknown";
    }
}

std::ostream& operator<<(std::ostream& out, const CureHealth& cureHealth) {
    out << cureHealth.value() << toString(cureHealth.valueType()) << '\n';
    if (not cureHealth.effects().empty()) {
        out << " {Effects: ";
        for (const auto& effect : cureHealth.effects()) {
            out << effect.effectType() << effect.duration();
        }
        out << "}";
    }
    return out;
}
