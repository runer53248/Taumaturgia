#pragma once

struct Damage {
    Damage() = default;
    explicit Damage(int value) : value_{value} {}
    auto& value() { return value_; }
    auto value() const { return value_; }

    auto operator<=>(const Damage& rhs) const = default;
    
private:
    int value_{};
};
