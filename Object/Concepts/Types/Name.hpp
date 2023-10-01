#pragma once
#include <string>

struct Name {
    Name() = default;
    explicit Name(const std::string& value)
        : value_{value} {}

    friend auto operator<=>(const Name& lhs, const Name& rhs) noexcept = default;

    operator std::string() noexcept { return value_; }
    operator std::string() const noexcept { return value_; }

private:
    std::string value_{};
};
