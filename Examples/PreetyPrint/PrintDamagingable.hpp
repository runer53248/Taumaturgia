#pragma once
#include <iostream>
#include "../../Object/Concepts/Damagingable.hpp"
#include "PrintDamageType.hpp"
#include "PrintDuration.hpp"
#include "PrintEffectType.hpp"

auto& operator<<(std::ostream& out, Damagingable auto& obj) {
    Damage dmg = obj.dmg;
    out << " for " << dmg.value() << " dmg";
    out << " with " << static_cast<std::string>(obj.name);
    out << " " << dmg.effect().effectType();
    out << " " << dmg.effect().duration();
    out << " " << dmg.type();
    return out;
}
