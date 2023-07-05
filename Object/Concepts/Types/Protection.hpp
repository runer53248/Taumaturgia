#pragma once
#include <array>
#include <numeric>
#include "ArmorClass.hpp"

struct Protection {
    Protection() noexcept = default;
    Protection(const ArmorClass& ac) noexcept
        : ac_{ac} {}
    Protection(auto&&... args) noexcept  // no explicit gives some oportunities
        requires std::is_constructible_v<ArmorClass, decltype(std::forward<decltype(args)>(args))...>
        : ac_{std::forward<decltype(args)>(args)...} {}

    auto operator<=>(const Protection& other) const noexcept = default;

    auto armorClass() const noexcept {
        return ac_.armorClass();
    }

    auto location() const noexcept {
        return ac_.location();
    }

    auto& protectEffects() & noexcept {
        return ac_.protectEffects();
    }
    auto protectEffects() && noexcept {
        return ac_.protectEffects();
    }
    auto& protectEffects() const& noexcept {
        return ac_.protectEffects();
    }
    auto protectEffects() const&& noexcept {
        return ac_.protectEffects();
    }

private:
    ArmorClass ac_{};
    // restance
    // spellResistance
    // damageReduction
    // protectionEffect
};
