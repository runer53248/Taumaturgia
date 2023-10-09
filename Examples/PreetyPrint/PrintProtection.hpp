#pragma once
#include <iostream>
#include "../../Object/Concepts/Types/Protection.hpp"
#include "../../Object/Concepts/Types/ArmorClass.hpp"
#include "PrintBodyLocation.hpp"
#include "PrintEffectType.hpp"

std::ostream& operator<<(std::ostream& out, const ArmorClass& ac) {
    out << "(Ac: " << ac.armorClass() << " to " << ac.location() << ") ";
    if (not ac.protectEffects().empty()) {
        out << "(protection";
        for (const auto& effect : ac.protectEffects()) {
            out << effect;
        }
        out << ") ";
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Protection& protection) {
    auto ac = protection.armorClass();
    auto location = protection.location();
    auto effects = protection.protectEffects();
    out << "(Ac: " << ac << " to " << location << ") ";
    if (not effects.empty()) {
        out << "(protection";
        for (const auto& effect : effects) {
            out << effect;
        }
        out << ") ";
    }
    return out;
}