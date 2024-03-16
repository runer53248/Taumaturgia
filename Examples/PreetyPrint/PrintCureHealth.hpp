#pragma once
#include <iostream>
#include "Object/Concepts/Types/CureHealth.hpp"
#include "PrintEffectContainer.hpp"

constexpr const char* toString(CureValueType type) noexcept {
    switch (type) {
    case CureValueType::VALUE:
        return " points";
    case CureValueType::CURRENT_PERCENT:
        return " %curent";
    case CureValueType::MAX_PERCENT:
        return " %max";
    default:
        return " Unknown";
    }
}

constexpr auto& operator<<(std::ostream& out, const CureHealth& cureHealth) {
    out << cureHealth.value() << toString(cureHealth.valueType()) << " hp";
    out << cureHealth.effects();
    return out;
}
