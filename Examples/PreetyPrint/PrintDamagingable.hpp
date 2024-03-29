#pragma once
#include <iostream>
#include "Object/Concepts/Damagingable.hpp"
#include "Object/Concepts/Traits/NameTraits.hpp"
#include "PrintDamageType.hpp"
#include "PrintDuration.hpp"
#include "PrintEffectType.hpp"

constexpr auto& operator<<(std::ostream& out, const Damagingable auto& obj) {
    const auto dmg = traits::accessDamage::get(obj);
    const auto name = traits::accessName::get(obj);
    out << " for " << dmg.value() << " dmg"
        << " with " << name
        << " " << dmg;
    return out;
}
