#pragma once
#include <iostream>
#include "PrintDuration.hpp"
#include "PrintEffectState.hpp"
#include "PrintEffectType.hpp"
#include "PrintWrapper.hpp"
#include "Usage/Types/Structs/Effect.hpp"

auto& operator<<(std::ostream& out, const Effect& effect) {
    auto effectType = effect.effectType();
    if (effectType == EffectType::None) {
        return out;
    }
    out << '[' << effectType << '|' << effect.duration() << '|' << effect.state() << ']';
    return out;
}
