#pragma once
#include "Effect.hpp"
#include "EffectContainer.hpp"

struct Hp {
    constexpr Hp() noexcept = default;
    constexpr explicit Hp(int value) noexcept : value_{value} {}
    constexpr Hp(int value, const Effect& effect) noexcept : value_{value}, effects_{EffectContainer{effect}} {}
    constexpr Hp(int value, std::initializer_list<Effect> effects) noexcept : value_{value}, effects_{effects} {}
    constexpr Hp(int value, const EffectContainer& effects) noexcept : value_{value}, effects_{effects} {}

    auto operator<=>(const Hp& other) const noexcept = default;

    auto& value() noexcept { return value_; }
    auto value() const noexcept { return value_; }

    auto& effects() { return effects_; }
    auto effects() const { return effects_; }

private:
    int value_{};
    EffectContainer effects_{};
};
