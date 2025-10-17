#pragma once
#include <algorithm>

struct HealthRange {
    constexpr HealthRange(int value) noexcept
        : current{value} {}
    constexpr HealthRange(int value, int limit) noexcept
        : limit{std::max(1, limit)}, current{std::min(value, this->limit)} {}

    constexpr int getValue() const noexcept {
        return current;
    }
    constexpr int getLimit() const noexcept {
        return limit;
    }

    static constexpr int default_max = 200;

private:
    int limit{default_max};
    int current{};
};
