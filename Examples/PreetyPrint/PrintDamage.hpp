#pragma once
#include <iostream>
#include "Usage/Types/Damage/Damage.hpp"
#include "PrintDamageType.hpp"
#include "PrintEffect.hpp"

#include "PrintWrapper.hpp"

auto& operator<<(std::ostream& out, const Damage& damage) {
    auto damageValue = damage.value();
    auto damageEffect = damage.effect();
    if (damageValue) {
        return print_in_round_braces(
            out, "Damage",
            [&] {
                out << damageValue << ' ' << damage.type();
                if (not damageEffect.empty()) {
                    out << ' ' << damageEffect;
                }
            });
    }
    if (not damageEffect.empty()) {
        return print_in_round_braces(
            out, "Effect",
            [&] {
                out << damageEffect;
            });
    }
    return out;
}
