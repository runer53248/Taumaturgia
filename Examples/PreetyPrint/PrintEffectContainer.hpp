#pragma once
#include <iostream>
#include "Object/Concepts/Types/EffectContainer.hpp"
#include "PrintEffectType.hpp"
#include "PrintDuration.hpp"

constexpr auto& operator<<(std::ostream& out, const EffectContainer& effectContainer) {
    if (not effectContainer.empty()) {
        out << " {Effects: ";
        for (const auto& effect : effectContainer) {
            out << effect.effectType() << effect.duration();
        }
        out << "}";
    }
    return out;
}
