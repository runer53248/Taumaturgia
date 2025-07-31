#pragma once
#include <iostream>
#include <ranges>
#include "PrintEffect.hpp"
#include "Usage/Types/Structs/EffectContainer.hpp"

auto& operator<<(std::ostream& out, const EffectContainer& effectContainer) {
    if (effectContainer.empty()) {
        return out;
    }
    return print_in_curly_braces(
        out, "Effects",
        [&] {
            for (const auto& effect : effectContainer | std::views::take(1)) {
                out << effect;
            }
            for (const auto& effect : effectContainer | std::views::drop(1)) {
                out << ", " << effect;
            }
        });
}
