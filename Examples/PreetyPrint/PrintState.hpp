#pragma once
#include <iostream>
#include "Object/Concepts/Types/State.hpp"
#include "PrintEffectState.hpp"

auto& operator<<(std::ostream& out, const State& state) {
    out << state.effectState();
    return out;
}
