#pragma once
#include "Enums/BodyLocation.hpp"
#include <array>
#include <numeric>

struct AC {
    constexpr AC() noexcept = default;
    constexpr explicit AC(int value) noexcept {
        values_.at(static_cast<size_t>(location_)) = value;
    }
    constexpr AC(int value, BodyLocation location) noexcept : location_{location} {
        if (location_ == BodyLocation::ALL) { // value ignored
            return;
        }
        values_.at(static_cast<size_t>(location_)) = value;
    }
    constexpr AC(int value, BodyLocation location, Effect effect) noexcept : location_{location}, effect_{effect} {
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

    auto& effect() noexcept { return effect_; }
    auto effect() const noexcept { return effect_; }

private:
    std::array<int, static_cast<size_t>(BodyLocation::ALL)> values_{};
    BodyLocation location_{BodyLocation::Body};
    Effect effect_{};
};
