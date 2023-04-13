#pragma once
#include "Effect.hpp"

struct Hp {
    Hp() = default;
    constexpr explicit Hp(int value) : value_{value} {}
    auto& value() { return value_; }
    auto value() const { return value_; }
    auto& effect() { return effect_; }
    auto effect() const { return effect_; }

    auto operator<=>(const Hp& rhs) const = default;
    
private:
    int value_{};
    Effect effect_{};
};
