#pragma once
#include <iostream>
#include "PrintDamageType.hpp"
#include "PrintDuration.hpp"
#include "PrintEffectType.hpp"

constexpr auto& operator<<(std::ostream& out, const Damagingable auto& obj) {
    const auto dmg = trait<Damage>::get(obj);
    const auto name = trait<Name>::get(obj);
    out 
    // << " for " << dmg.value() << " dmg"
        << " with "
        << Color::Green << name << Color::Reset
        << " " << dmg;
    return out;
}
