#pragma once
#include <iostream>
#include "../../Object/Concepts/Types/Damage.hpp"
#include "PrintDamageType.hpp"
#include "PrintDuration.hpp"
#include "PrintEffectState.hpp"
#include "PrintEffectType.hpp"

std::ostream& operator<<(std::ostream& out, const Damage& damage) {
    std::cout << "(Damage: " << damage.value() << damage.type() << damage.effect().effectType() << damage.effect().duration();
    std::cout << damage.effect().state().effectState();
    std::cout << ")";
    return out;
}
