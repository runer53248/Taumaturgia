#pragma once
#include <iostream>
#include "../../Object/Concepts/Types/Enums/EffectType.hpp"

constexpr const char* toString(EffectType effect) noexcept {
    switch (effect) {
    case EffectType::Infection:
        return "Infection";
    case EffectType::Bleed:
        return "bleed";
    case EffectType::Burn:
        return "burn";
    case EffectType::Sleep:
        return "sleep";
    case EffectType::Daze:
        return "Daze";
    case EffectType::Devour:
        return "devour";
    case EffectType::Stun:
        return "stunned";
    case EffectType::Shock:
        return "Shock";
    case EffectType::None:
        return "none";
    case EffectType::Freeze:
        return "freeze";
    case EffectType::Slow:
        return "Slow]";
    case EffectType::Paralyze:
        return "Paralyze";
    case EffectType::Dazzle:
        return "Dazzle";
    case EffectType::Poison:
        return "Poison";
    case EffectType::Contagion:
        return "Contagion";
    case EffectType::Smite:
        return "Smite";
    case EffectType::Petryfy:
        return "Petryfy";
    default:
        return "Unknown";
    }
}

auto& operator<<(std::ostream& out, EffectType effect) {
    out << " [" << toString(effect) << "]";
    return out;
}
