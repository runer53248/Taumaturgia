#pragma once
#include "UnorderedCtor.hpp"
#include "Usage/Properties.hpp"

struct Base {
    Base() noexcept = default;

    Base(int x, int y) noexcept
        : x{x}, y{y} {}

    UnorderedCtor(Base);

    template <typename T, size_t = 0, typename Self>
    constexpr decltype(auto) getType(this Self& self) noexcept {
        if constexpr (std::same_as<T, int>) {
            return (self.type1);
        }
        if constexpr (std::same_as<T, float>) {
            return (self.type2);
        }
    }

    int x{};
    int y{};
    Name name;
    // Damage dmg;
    // Health hp;
    Protection protection;
    double type{};

private:
    int type1{};
    float type2{};
};
