#pragma once

struct Hp {
    Hp() = default;
    explicit Hp(int value) : value_{value} {}
    operator int() {
        return value_;
    }
private:
    int value_{};
};
