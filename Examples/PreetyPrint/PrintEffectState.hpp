#pragma once
#include <iostream>
#include "Taumaturgia/Types/Enums/EffectState.hpp"

constexpr const char* toString(EffectState state) noexcept {
    switch (state) {
    case EffectState::Inactive:
        return "Inactive";
    case EffectState::Active:
        return "Active";
    case EffectState::Removed:
        return "Removed";
    case EffectState::Ended:
        return "Ended";
    default:
        return "Unknown";
    }
}

auto& operator<<(std::ostream& out, EffectState state) {
    return out << '[' << toString(state) << ']';
}
