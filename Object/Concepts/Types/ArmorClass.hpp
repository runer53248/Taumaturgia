#pragma once
#include <array>
#include <numeric>
#include "EffectTypeContainer.hpp"
#include "Enums/BodyLocation.hpp"

struct ArmorClass {
    ArmorClass() noexcept = default;
    explicit ArmorClass(int value) noexcept
        : value_{value} {}
    ArmorClass(int value, BodyLocation location) noexcept
        : ArmorClass(value, location, {}) {}
    ArmorClass(int value, BodyLocation location, std::initializer_list<EffectType> protectEffects) noexcept
        : value_{value}, location_{location}, protectEffects_{protectEffects} {
        if (location_ >= BodyLocation::ALL or location_ == BodyLocation::NONE) {
            location_ = BodyLocation::NONE;
            value_ = 0;
        }
    }

    auto operator<=>(const ArmorClass& other) const noexcept = default;

    auto armorClass() const noexcept { return value_; }
    auto location() const noexcept { return location_; }
    auto& protectEffects() & noexcept { return protectEffects_; }
    auto protectEffects() && noexcept { return protectEffects_; }
    auto& protectEffects() const& noexcept { return protectEffects_; }
    auto protectEffects() const&& noexcept { return protectEffects_; }

private:
    int value_{};
    BodyLocation location_{BodyLocation::Body};
    EffectTypeContainer protectEffects_{};
};
