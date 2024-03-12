#pragma once
#include <iostream>
#include "../../Object/Concepts/Types/Damage.hpp"
#include "PrintDamageType.hpp"
#include "PrintDuration.hpp"
#include "PrintEffectState.hpp"
#include "PrintEffectType.hpp"

auto& operator<<(std::ostream& out, const Damage& damage) {
    out << "(Damage: " << damage.value() << damage.type() << damage.effect().effectType() << damage.effect().duration();
    out << damage.effect().state().effectState();
    out << ")";
    return out;
}
