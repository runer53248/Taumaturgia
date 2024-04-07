#pragma once
#include <iostream>
#include "Taumaturgia/Types/Health.hpp"
#include "PrintWrapper.hpp"

auto& operator<<(std::ostream& out, const Health& health) {
    return print_in_round_braces(
        out, "Health",
        [&] {
            out << health.value() << " hp / " << health.maxValue() << " hp";

            if (health.effects().empty()) {
                return;
            }
            out << ' ';
            print_in_curly_braces(
                out, "Effects",
                [&] {
                    for (const auto& effect : health.effects()) {
                        out << effect.effectType() << effect.duration();
                    }
                });
        });
}
