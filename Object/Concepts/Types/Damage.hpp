#pragma once
#include "Effect.hpp"

struct Damage {
    constexpr Damage() = default;
    constexpr explicit Damage(int value) : value_{value} {}
    constexpr Damage(int value, Effect effect) : value_{value}, effect_{effect} {}

    auto operator<=>(const Damage& rhs) const = default;

    auto& value() { return value_; }
    auto value() const { return value_; }

    auto& effect() { return effect_; }
    auto effect() const { return effect_; }
    
private:
    int value_{};
    Effect effect_{};
};
