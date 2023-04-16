#pragma once
#include <array>
#include <numeric>
#include "Enums/BodyLocation.hpp"
#include "EffectTypeContainer.hpp"

struct ArmorClass {
    ArmorClass() noexcept = default;
    explicit ArmorClass(int value) noexcept : value_{value} {}
    ArmorClass(int value, BodyLocation location) noexcept : value_{value}, location_{location} {
        if (location_ >= BodyLocation::ALL or location_ == BodyLocation::NONE) {
            location_ = BodyLocation::NONE;
            value_ = 0;
        }
    }
    ArmorClass(int value, BodyLocation location, EffectTypeContainer protectEffects) noexcept : value_{value}, location_{location}, protectEffects_{protectEffects} {
        if (location_ >= BodyLocation::ALL or location_ == BodyLocation::NONE) {
            location_ = BodyLocation::NONE;
            value_ = 0;
        }
    }

    auto operator<=>(const ArmorClass& other) const noexcept = default;

    auto value() const noexcept { return value_; }

    auto location() const noexcept { return location_; }

    auto& protectEffects() & noexcept { return protectEffects_; }
    auto protectEffects() && noexcept { return protectEffects_; }
    auto& protectEffects() const & noexcept { return protectEffects_; }
    auto protectEffects() const && noexcept { return protectEffects_; }

private:
    int value_{};
    BodyLocation location_{BodyLocation::Body};
    EffectTypeContainer protectEffects_{};
};
