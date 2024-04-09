#pragma once
#include <limits>
#include "Effect.hpp"
#include "EffectContainer.hpp"

class Health {
public:
    constexpr Health() noexcept = default;
    constexpr explicit Health(int value) noexcept
        : value_{std::min(value, MAX_VALUE)} {}
    constexpr Health(int value, const Effect& effect) noexcept
        : value_{std::min(value, MAX_VALUE)}, effects_{EffectContainer{effect}} {}
    constexpr Health(int value, const EffectContainer& effects) noexcept
        : value_{std::min(value, MAX_VALUE)}, effects_{effects} {}

    constexpr auto operator<=>(const Health& other) const noexcept = default;

    void value(int value) noexcept { value_ = std::min(value, MAX_VALUE); }
    constexpr auto value() const noexcept { return value_; }
    constexpr auto maxValue() const noexcept { return MAX_VALUE; }

    auto& effects() & noexcept { return effects_; }
    auto effects() && noexcept { return effects_; }
    auto& effects() const& noexcept { return effects_; }
    auto effects() const&& noexcept { return effects_; }

    void addHealth(int value) {
        if (value <= 0) {
            return;
        }
        auto range = std::minmax(value, value_);

        if (MAX_VALUE - range.second < range.first) {
            value_ = MAX_VALUE;
            return;
        }
        value_ += value;
    }

    void removeHealth(int value) {
        if (value <= 0) {
            return;
        }
        auto range = std::minmax(value, value_);

        if (std::numeric_limits<int>::min() + range.second > range.first) {
            value_ = std::numeric_limits<int>::min();
            return;
        }
        value_ -= value;
    }

private:
    int value_{};
    EffectContainer effects_{};
    static constexpr int MAX_VALUE = 200;
};
