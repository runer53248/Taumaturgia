#pragma once
#include <limits>
#include "Structs/EffectContainer.hpp"
#include "Health.hpp"

enum class CureValueType {
    VALUE,
    CURRENT_PERCENT,
    MAX_PERCENT
};

class CureHealth {
public:
    constexpr CureHealth() noexcept = default;
    constexpr explicit CureHealth(int value) noexcept
        : value_{value} {}
    constexpr CureHealth(int value, CureValueType type) noexcept
        : value_{value}, value_type_{type} {}
    constexpr CureHealth(int value, const Effect& effect) noexcept
        : value_{value}, effects_{EffectContainer{effect}} {}
    constexpr CureHealth(int value, const EffectContainer& effects) noexcept
        : value_{value}, effects_{effects} {}

    constexpr auto operator<=>(const CureHealth& other) const noexcept = default;

    void value(int value, CureValueType type) noexcept;

    constexpr auto value() const& noexcept { return value_; }
    constexpr auto valueType() const& noexcept { return value_type_; }

    auto& effects() & noexcept { return effects_; }
    auto& effects() const& noexcept { return effects_; }
    template <typename Self>
    auto effects(this Self&& self) noexcept { return std::forward<Self>(self).effects_; }

    void applyOn(Health& health) const noexcept;

private:
    int value_{};
    CureValueType value_type_{CureValueType::VALUE};
    EffectContainer effects_{};
};

inline void CureHealth::value(int value, CureValueType type) noexcept {
    value_ = value;
    value_type_ = type;
}

inline void CureHealth::applyOn(Health& health) const noexcept {
    if (health.value() <= 0) {
        return;
    }

    int change_value{};
    switch (value_type_) {
    case CureValueType::VALUE:
        change_value = value_;
        break;
    case CureValueType::CURRENT_PERCENT:
        change_value = health.value() * value_ / 100;
        break;
    case CureValueType::MAX_PERCENT:
        change_value = health.maxValue() * value_ / 100;
        break;
    default:
        return;
    }

    health.addHealth(change_value);
}
