#pragma once
#include <array>
#include <numeric>

enum class BodyLocation {
    Head,
    Body,
    Arms,
    Legs,
    Internal,
    ALL // used as number of elements for array and as special value to accumulate values from it
};

struct AC {
    AC() = default;
    explicit AC(int value) {
        values_.at(static_cast<size_t>(location_)) = value;
    }
    AC(int value, BodyLocation location) : location_{location} {
        if (location_ == BodyLocation::ALL) { // value ignored
            return;
        }
        values_.at(static_cast<size_t>(location_)) = value;
    }

    auto value() const {
        if (location_ == BodyLocation::ALL) {
            return std::accumulate(values_.cbegin(), values_.cend(), 0);
        }
        return values_.at(static_cast<size_t>(location_));
    }
    auto& value(BodyLocation location) { 
        return values_.at(static_cast<size_t>(location));
    }
    auto value(BodyLocation location) const { 
        return values_.at(static_cast<size_t>(location));
    }

    auto location() const { return location_; }

    auto operator<=>(const AC& rhs) const = default;

private:
    std::array<int, static_cast<size_t>(BodyLocation::ALL)> values_{};
    BodyLocation location_{BodyLocation::Body};
};
