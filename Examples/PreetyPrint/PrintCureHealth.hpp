#pragma once
#include <iostream>
#include "Taumaturgia/Types/CureHealth.hpp"
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

auto& operator<<(std::ostream& out, const CureHealth& cureHealth) {
    const auto& effects = cureHealth.effects();

    return print_in_round_braces(
        out, "Cure",
        [&] {
            out << cureHealth.value()
                << toString(cureHealth.valueType()) << " hp";
            if (effects.empty()) {
                return;
            }
            out << ' ';
            out << effects;
        });
}
