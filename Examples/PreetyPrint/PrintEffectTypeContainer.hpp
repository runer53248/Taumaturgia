#pragma once
#include <iostream>
#include "Usage/Types/EffectTypeContainer.hpp"
#include "PrintEffectType.hpp"

auto& operator<<(std::ostream& out, const EffectTypeContainer& effectTypes) {
    const auto& effects = effectTypes.effectTypes();
    for (const auto& effect : effects) {
        out << effect;
    }
    return out;
}
