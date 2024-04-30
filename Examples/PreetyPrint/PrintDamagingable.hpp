#pragma once
#include <iostream>
#include "Taumaturgia/Traits/DamageTraits.hpp"
#include "Taumaturgia/Traits/NameTraits.hpp"
#include "PrintDamageType.hpp"
#include "PrintDuration.hpp"
#include "PrintEffectType.hpp"

constexpr auto& operator<<(std::ostream& out, const Damagingable auto& obj) {
    const auto dmg = Damagingable_trait::get(obj);
    const auto name = traits::accessName::get(obj);
    out << " for " << dmg.value() << " dmg"
        << " with " << name
        << " " << dmg;
    return out;
}
