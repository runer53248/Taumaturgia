#pragma once

struct Damage {
    Damage() = default;
    explicit Damage(int value) : value_{value} {}
    operator int() {
        return value_;
    }
private:
    int value_{};
};
