#pragma once
#include "Structs/Effect.hpp"
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
    template <typename Self>
    constexpr auto value(this Self&& self) noexcept { return std::forward<Self>(self).value_; }

    auto type() const noexcept { return type_; }

    auto& effect() & noexcept { return effect_; }
    template <typename Self>
    constexpr auto effect(this Self&& self) noexcept { return std::forward<Self>(self).effect_; }

private:
    int value_{};
    DamageType type_{DamageType::Physical};
    Effect effect_{};
};
