#pragma once
#include "Enums/BodyLocation.hpp"
#include "EffectTypeContainer.hpp"
#include <array>
#include <numeric>

struct AC {
    AC() noexcept = default;
    explicit AC(int value) noexcept {
        values_.at(static_cast<size_t>(location_)) = value;
    }
    AC(int value, BodyLocation location) noexcept : location_{location} {
        if (location_ == BodyLocation::ALL) { // value ignored
            return;
        }
        values_.at(static_cast<size_t>(location_)) = value;
    }
    AC(int value, BodyLocation location, EffectTypeContainer protectEffects) noexcept : location_{location}, protectEffects_{protectEffects} {
        if (location_ == BodyLocation::ALL) { // value ignored
            return;
        }
        values_.at(static_cast<size_t>(location_)) = value;
    }

    auto operator<=>(const AC& other) const noexcept = default;

    auto value() const {
        if (location_ == BodyLocation::ALL) {
            return std::accumulate(values_.cbegin(), values_.cend(), 0);
        }
        return values_.at(static_cast<size_t>(location_));
    }
    auto& value(BodyLocation location) noexcept { 
        return values_.at(static_cast<size_t>(location));
    }
    auto value(BodyLocation location) const noexcept { 
        return values_.at(static_cast<size_t>(location));
    }

    auto location() const noexcept { return location_; }

    auto& protectEffects() & noexcept { return protectEffects_; }
    auto protectEffects() && noexcept { return protectEffects_; }
    auto& protectEffects() const & noexcept { return protectEffects_; }
    auto protectEffects() const && noexcept { return protectEffects_; }

private:
    std::array<int, static_cast<size_t>(BodyLocation::ALL)> values_{};
    BodyLocation location_{BodyLocation::Body};
    EffectTypeContainer protectEffects_{};
};
