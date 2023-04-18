#pragma once
#include "Effect.hpp"
#include "Enums/DamageType.hpp"

struct Damage {
    constexpr Damage() = default;
    constexpr explicit Damage(int value)
        : value_{value} {}
    constexpr Damage(int value, DamageType type)
        : value_{value}, type_{type} {}
    constexpr Damage(int value, Effect effect)
        : value_{value}, effect_{effect} {}
    constexpr Damage(int value, DamageType type, Effect effect)
        : value_{value}, type_{type}, effect_{effect} {}

    auto operator<=>(const Damage& rhs) const = default;

    auto& value() & { return value_; }
    auto value() && { return value_; }
    auto value() const& { return value_; }
    auto value() const&& { return value_; }

    auto type() const { return type_; }

    auto& effect() & { return effect_; }
    auto effect() && { return effect_; }
    auto effect() const& { return effect_; }
    auto effect() const&& { return effect_; }

private:
    int value_{};
    DamageType type_{DamageType::Physical};
    Effect effect_{};
};
