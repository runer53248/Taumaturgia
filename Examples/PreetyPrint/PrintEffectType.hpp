#pragma once
#include <iostream>
#include "Object/Concepts/Types/Enums/EffectType.hpp"

constexpr const char* toString(EffectType effect) noexcept {
    switch (effect) {
    case EffectType::Infection:
        return "Infection";
    case EffectType::Bleed:
        return "Bleed";
    case EffectType::Burn:
        return "Burn";
    case EffectType::Sleep:
        return "Sleep";
    case EffectType::Daze:
        return "Daze";
    case EffectType::Devour:
        return "Devour";
    case EffectType::Stun:
        return "Stun";
    case EffectType::Shock:
        return "Shock";
    case EffectType::None:
        return "None";
    case EffectType::Freeze:
        return "Freeze";
    case EffectType::Slow:
        return "Slow";
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

constexpr auto& operator<<(std::ostream& out, EffectType effect) {
    return out << " [" << toString(effect) << "]";
}
