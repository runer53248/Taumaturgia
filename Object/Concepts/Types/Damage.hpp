#pragma once
#include "Effect.hpp"

struct Damage {
    Damage() = default;
    explicit Damage(int value) : value_{value} {}
    Damage(int value, Effect effect) : value_{value}, effect_{effect} {}
    auto& value() { return value_; }
    auto value() const { return value_; }
    auto& effect() { return effect_; }
    auto effect() const { return effect_; }
    
    auto operator<=>(const Damage& rhs) const = default;
    
private:
    int value_{};
    Effect effect_{};
};
