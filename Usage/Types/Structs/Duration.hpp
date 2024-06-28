#pragma once
#include <stddef.h>
#include <array>
#include "Usage/Types/Enums/DurationType.hpp"

class Duration {
public:
    constexpr Duration() noexcept = default;
    constexpr Duration(size_t value, DurationType type) noexcept
        : value_{value}, type_{type} {}

    constexpr auto operator<=>(const Duration& other) const noexcept = default;

    auto& value() & noexcept { return value_; }
    template <typename Self>
    auto value(this Self&& self) noexcept { return std::forward<Self>(self).value_; }


    auto& type() & noexcept { return type_; }
    template <typename Self>
    auto type(this Self&& self) noexcept { return std::forward<Self>(self).type_; }

    // return true if duration ended
    bool timePass(Duration timedelta) noexcept;

private:
    size_t value_{1};
    DurationType type_{DurationType::Round};
};

inline bool Duration::timePass(Duration timedelta) noexcept {
    size_t time_left = static_cast<size_t>(type_) * value_;
    size_t time_pass = static_cast<size_t>(timedelta.type()) * timedelta.value();

    if (time_pass >= time_left) {
        value_ = 0;
        return true;
    }

    if (type_ == timedelta.type()) {
        value_ -= timedelta.value();
        return false;
    }

    time_left -= time_pass;

    std::array leftTypes{
        DurationType::Day,
        DurationType::Hour,
        DurationType::Minute,
        DurationType::Round,
        DurationType::Action};

    for (auto leftType : leftTypes) {
        if (time_left % static_cast<size_t>(leftType) == 0) {
            type_ = leftType;
            value_ = time_left / static_cast<size_t>(leftType);
            return false;
        }
    }
    type_ = DurationType::Instant;
    value_ = 0;
    return true;
}
