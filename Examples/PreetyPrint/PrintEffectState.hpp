#pragma once
#include <iostream>
#include "Color_print.hpp"
#include "Usage/Enums/EffectState.hpp"

constexpr const char* toString(EffectState state) noexcept {
    switch (state) {
    case EffectState::Inactive:
        return "Inactive";
    case EffectState::Active:
        return "Active";
    case EffectState::Removed:
        return "Removed";
    case EffectState::Finished:
        return "Finished";
    default:
        return "Unknown";
    }
}

template <typename T>
auto& operator<<(std::ostream& out, std::pair<T, EffectState> target) {
    if (target.second == EffectState::Inactive) {
        return out << Color::GreyBack << target.first << Color::Reset;
    } else if (target.second == EffectState::Active) {
        return out << Color::GreenBack << target.first << Color::Reset;
    } else if (target.second == EffectState::Removed) {
        return out << Color::YellowBack << target.first << Color::Reset;
    } else if (target.second == EffectState::Finished) {
        return out << Color::RedBack << target.first << Color::Reset;
    } else {
        return out << target.first;
    }
}

auto& operator<<(std::ostream& out, EffectState state) {
    return out << '[' << toString(state) << ']';
}
