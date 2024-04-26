#pragma once
#include <array>
#include <numeric>
#include "ArmorClass.hpp"

class Protection {
public:
    Protection() noexcept = default;
    Protection(const ArmorClass& ac) noexcept
        : ac_{ac} {}

    template <typename... Args>
        requires std::is_constructible_v<ArmorClass, Args...>
    Protection(Args&&... args) noexcept  // no explicit gives some oportunities
        : ac_{std::forward<Args>(args)...} {}

    std::strong_ordering operator<=>(const Protection& other) const noexcept = default;

    decltype(auto) armorClass() const noexcept { return ac_.armorClass(); }
    decltype(auto) location() const noexcept { return ac_.location(); }

    decltype(auto) protectEffects() & noexcept { return ac_.protectEffects(); }
    decltype(auto) protectEffects() && noexcept { return ac_.protectEffects(); }
    decltype(auto) protectEffects() const& noexcept { return ac_.protectEffects(); }
    decltype(auto) protectEffects() const&& noexcept { return ac_.protectEffects(); }

private:
    ArmorClass ac_{};
    // restance
    // spellResistance
    // damageReduction
    // protectionEffect
};