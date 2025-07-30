#pragma once
#include <iostream>
#include "Color_print.hpp"
#include "Usage/Enums/EffectType.hpp"

constexpr std::string toString(EffectType effect) noexcept {
    switch (effect) {
    case EffectType::Infection:
        return Color::Green + "Infection" + Color::Reset;
    case EffectType::Bleed:
        return Color::Red + "Bleed" + Color::Reset;
    case EffectType::Burn:
        return Color::Red + "Burn" + Color::Reset;
    case EffectType::Sleep:
        return Color::Blue + "Sleep" + Color::Reset;
    case EffectType::Daze:
        return "Daze";
    case EffectType::Devour:
        return Color::Green + "Devour" + Color::Reset;
    case EffectType::Stun:
        return Color::White + "Stun" + Color::Reset;
    case EffectType::Shock:
        return Color::Yellow+ "Shock" + Color::Reset;
    case EffectType::None:
        return "None";
    case EffectType::Freeze:
        return Color::Blue + "Freeze" + Color::Reset;
    case EffectType::Slow:
        return "Slow";
    case EffectType::Paralyze:
        return "Paralyze";
    case EffectType::Dazzle:
        return "Dazzle";
    case EffectType::Poison:
        return Color::Green + "Poison" + Color::Reset;
    case EffectType::Contagion:
        return Color::Green + "Contagion" + Color::Reset;
    case EffectType::Smite:
        return "Smite";
    case EffectType::Petryfy:
        return "Petryfy";
    default:
        return "Unknown";
    }
}

auto& operator<<(std::ostream& out, EffectType effect) {
    return out << '[' << toString(effect) << ']';
}
