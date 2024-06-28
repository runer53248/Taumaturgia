#pragma once
#include <array>
#include <numeric>
#include "Usage/Types/EffectTypeContainer.hpp"
#include "Usage/Types/Enums/BodyLocation.hpp"

class ArmorClass {
public:
    ArmorClass() noexcept = default;
    explicit ArmorClass(int value) noexcept
        : value_{value} {}
    ArmorClass(int value, BodyLocation location) noexcept
        : ArmorClass(value, location, {}) {}
    ArmorClass(int value, BodyLocation location, std::initializer_list<EffectType> protectEffects) noexcept;

    std::strong_ordering operator<=>(const ArmorClass& other) const noexcept = default;

    auto armorClass() const noexcept { return value_; }
    auto location() const noexcept { return location_; }

    auto& protectEffects() & noexcept { return protectEffects_; }
    auto& protectEffects() const& noexcept { return protectEffects_; }
    template <typename Self>
    auto protectEffects(this Self&& self) noexcept { return std::forward<Self>(self).protectEffects_; }

private:
    int value_{};
    BodyLocation location_{BodyLocation::Body};
    EffectTypeContainer protectEffects_{};
};

inline ArmorClass::ArmorClass(int value, BodyLocation location, std::initializer_list<EffectType> protectEffects) noexcept
    : value_{value}, location_{location}, protectEffects_{protectEffects} {
    if (location_ >= BodyLocation::ALL or location_ == BodyLocation::NONE) {
        location_ = BodyLocation::NONE;
        value_ = 0;
    }
}
