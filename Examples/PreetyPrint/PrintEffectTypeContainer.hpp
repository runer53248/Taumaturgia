#pragma once
#include <iostream>
#include "../../Object/Concepts/Types/EffectTypeContainer.hpp"
#include "PrintEffectType.hpp"

auto& operator<<(std::ostream& out, EffectTypeContainer effects) {
    out << "restore:";
    for (const auto& effect : effects.effectTypes()) {
        out << effect;
    }
    out << '\n';
    return out;
}
