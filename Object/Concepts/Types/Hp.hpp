#pragma once

struct Hp {
    Hp() = default;
    explicit Hp(int value) : value_{value} {}
    auto& value() { return value_; }
    auto value() const { return value_; }

    auto operator<=>(const Hp& rhs) const = default;
    
private:
    int value_{};
};
