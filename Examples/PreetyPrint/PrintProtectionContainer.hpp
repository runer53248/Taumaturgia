#pragma once
#include <iostream>
#include "../../Object/Concepts/Types/ProtectionContainer.hpp"
#include "PrintProtection.hpp"

constexpr auto& operator<<(std::ostream& out, const ProtectionContainer& armorWear) {
    out << "(armor class: " << armorWear.value() << ") ";

    if (not armorWear.protectEffects().empty()) {
        out << "(protection";
        for (const auto& effect : armorWear.protectEffects()) {
            out << effect;
        }
        out << ')';
    }
    const auto armorLocations = armorWear.getWearedLocations();
    for (auto location : armorLocations) {
        out << '\n';
        out << '\t' << armorWear.armorAtLocation(location).value();
    }
    return out;
}
