#pragma once
#include <iostream>
#include "PrintWrapper.hpp"
#include "Usage/Types/Health/Health.hpp"

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
                        out << effect.effectType()
                            << std::pair{effect.duration(), effect.state()};
                    }
                });
        });
}
