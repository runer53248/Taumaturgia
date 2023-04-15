#pragma once
#include <string>

struct Name {
    Name() = default;
    explicit Name(const std::string& value) : value_{value} {}

    auto operator<=>(const Name& other) const noexcept = default;

    operator std::string() noexcept { return value_; }
    operator std::string() const noexcept { return value_; }

private:
    std::string value_{};
};
