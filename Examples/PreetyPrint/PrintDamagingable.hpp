#pragma once
#include <iostream>
#include "../../Object/Concepts/Damagingable.hpp"
#include "PrintDamageType.hpp"
#include "PrintDuration.hpp"
#include "PrintEffectType.hpp"

constexpr auto& operator<<(std::ostream& out, const Damagingable auto& obj) {
    auto dmg = traits::accessDamage::get(obj);
    out << " for " << dmg.value() << " dmg";
    out << " with " << traits::accessName::get(obj);
    out << " " << dmg.effect().effectType();
    out << " " << dmg.effect().duration();
    out << " " << dmg.type();
    return out;
}
