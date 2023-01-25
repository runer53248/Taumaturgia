#pragma once

struct AC {
    AC() = default;
    explicit AC(int value) : value_{value} {}
    operator int() {
        return value_;
    }
private:
    int value_{};
};
