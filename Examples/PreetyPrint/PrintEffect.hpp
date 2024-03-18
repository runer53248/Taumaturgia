#pragma once
#include <iostream>
#include "Object/Concepts/Types/Effect.hpp"
#include "PrintDuration.hpp"
#include "PrintEffectType.hpp"
#include "PrintState.hpp"
#include "PrintWrapper.hpp"

constexpr auto& operator<<(std::ostream& out, const Effect& effect) {
    auto effectType = effect.effectType();
    if (effectType == EffectType::None) {
        return out;
    }
    out << '[' << effectType << '|' << effect.duration() << '|' << effect.state() << ']';
    return out;
}
