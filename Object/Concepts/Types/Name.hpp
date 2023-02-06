#pragma once
#include <string>

struct Name {
    Name() = default;
    explicit Name(const std::string& value) : value_{value} {}
    operator std::string() { return value_; }
    operator std::string() const { return value_; }

    auto operator<=>(const Name& rhs) const = default;

private:
    std::string value_{};
};
