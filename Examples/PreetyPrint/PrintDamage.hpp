#pragma once
#include <iostream>
#include "Object/Concepts/Types/Damage.hpp"
#include "PrintDamageType.hpp"
#include "PrintDuration.hpp"
#include "PrintEffectState.hpp"
#include "PrintEffectType.hpp"

#include "PrintWrapper.hpp"

auto& operator<<(std::ostream& out, const Damage& damage) {
    return print_in_round_braces(
        out, "Damage",
        [&] {
            out << damage.value() << ' ' << damage.type();
            if (damage.effect().empty()) {
                return;
            }
            out << ' ' << damage.effect();
        });
}
