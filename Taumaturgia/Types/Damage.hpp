#pragma once
#include "Effect.hpp"
#include "Enums/DamageType.hpp"

class Damage {
public:
    constexpr Damage() noexcept = default;
    constexpr explicit Damage(int value) noexcept
        : value_{value} {}
    constexpr Damage(int value, DamageType type) noexcept
        : value_{value}, type_{type} {}
    constexpr Damage(int value, Effect effect) noexcept
        : value_{value}, effect_{effect} {}
    constexpr Damage(int value, DamageType type, Effect effect) noexcept
        : value_{value}, type_{type}, effect_{effect} {}

    constexpr auto operator<=>(const Damage& rhs) const noexcept = default;

    auto& value() & noexcept { return value_; }
    auto value() && noexcept { return value_; }
    auto value() const& noexcept { return value_; }
    auto value() const&& noexcept { return value_; }

    auto type() const noexcept { return type_; }

    auto& effect() & noexcept { return effect_; }
    auto effect() && noexcept { return effect_; }
    auto effect() const& noexcept { return effect_; }
    auto effect() const&& noexcept { return effect_; }

private:
    int value_{};
    DamageType type_{DamageType::Physical};
    Effect effect_{};
};
