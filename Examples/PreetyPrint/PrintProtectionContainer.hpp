#pragma once
#include <iostream>
#include "PrintProtection.hpp"

std::ostream& operator<<(std::ostream& out, const ProtectionContainer& armorWear) {
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
