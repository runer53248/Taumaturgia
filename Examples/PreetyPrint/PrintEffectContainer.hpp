#pragma once
#include <iostream>
#include "Usage/Types/Structs/EffectContainer.hpp"
#include "PrintEffect.hpp"

auto& operator<<(std::ostream& out, const EffectContainer& effectContainer) {
    if (effectContainer.empty()) {
        return out;
    }
    return print_in_curly_braces(
        out, "Effects",
        [&] {
            for (const auto& effect : effectContainer) {
                out << effect;
            }
        });
}
