#pragma once
#include <iostream>
#include "Object/Concepts/Types/Enums/EffectType.hpp"

constexpr const char* toString(EffectType effect) noexcept {
    switch (effect) {
    case EffectType::Infection:
        return "\033[1;32mInfection\033[0m";
    case EffectType::Bleed:
        return "\033[1;31mBleed\033[0m";
    case EffectType::Burn:
        return "\033[1;31mBurn\033[0m";
    case EffectType::Sleep:
        return "\033[1;34mSleep\033[0m";
    case EffectType::Daze:
        return "Daze";
    case EffectType::Devour:
        return "\033[1;32mDevour\033[0m";
    case EffectType::Stun:
        return "\033[1;37mStun\033[0m";
    case EffectType::Shock:
        return "\033[1;33mShock\033[0m";
    case EffectType::None:
        return "None";
    case EffectType::Freeze:
        return "\033[1;34mFreeze\033[0m";
    case EffectType::Slow:
        return "Slow";
    case EffectType::Paralyze:
        return "Paralyze";
    case EffectType::Dazzle:
        return "Dazzle";
    case EffectType::Poison:
        return "\033[1;32mPoison\033[0m";
    case EffectType::Contagion:
        return "\033[1;32mContagion\033[0m";
    case EffectType::Smite:
        return "Smite";
    case EffectType::Petryfy:
        return "Petryfy";
    default:
        return "Unknown";
    }
}

constexpr auto& operator<<(std::ostream& out, EffectType effect) {
    return out << '[' << toString(effect) << ']';
}
