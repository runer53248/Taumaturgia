#pragma once
#include <string>

class Name {
public:
    Name() = default;
    explicit Name(const std::string& value)
        : value_{value} {}

    constexpr auto operator<=>(const Name& other) const noexcept = default;

    template <typename Self>
    constexpr operator std::string(this Self&& self) noexcept { return std::forward<Self>(self).value_; }
    constexpr operator std::string() const noexcept { return value_; }

private:
    std::string value_{};
};
