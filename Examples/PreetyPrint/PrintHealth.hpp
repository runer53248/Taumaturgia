#pragma once
#include <iostream>
#include "../../Object/Concepts/Types/Health.hpp"

std::ostream& operator<<(std::ostream& out, const Health& health) {
    out << health.value() << " hp / " << health.maxValue() << " hp";
    if (not health.effects().empty()) {
        out << " {Effects: ";
        for (const auto& effect : health.effects()) {
            out << effect.effectType() << effect.duration();
        }
        out << "}";
    }
    return out;
}
