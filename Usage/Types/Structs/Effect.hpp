#pragma once
#include <stdexcept>
#include <vector>
#include "Duration.hpp"
#include "Usage/Enums/EffectState.hpp"
#include "Usage/Enums/EffectType.hpp"

// enum class EffectStatusModifier {
//     Suspended,
//     Delayed,
//     Removed
// };

// struct StatusModifier {
//     Duration duration{};
//     EffectStatusModifier status{EffectStatusModifier::Suspended};
// };

class Effect {
public:
    constexpr Effect() noexcept = default;
    constexpr Effect(EffectType attackEffect, Duration duration, EffectState state) noexcept
        : effectType_{attackEffect}, duration_{duration}, state_{state} {}
    constexpr Effect(EffectType attackEffect, DurationType durationType) noexcept
        : Effect{attackEffect, Duration{1, durationType}, EffectState::Inactive} {}
    constexpr Effect(EffectType attackEffect, Duration duration) noexcept
        : Effect{attackEffect, duration, EffectState::Inactive} {}
    constexpr Effect(EffectType attackEffect, EffectState state) noexcept
        : effectType_{attackEffect}, duration_{Duration{1, DurationType::Round}}, state_{state} {}
    constexpr explicit Effect(EffectType attackEffect) noexcept
        : effectType_{attackEffect} {}

    constexpr auto operator<=>(const Effect& other) const noexcept = default;
    constexpr bool operator==(const Effect& other) const noexcept = default;
    
    constexpr auto& effectType() & noexcept { return effectType_; }
    template <typename Self>
    constexpr auto effectType(this Self&& self) noexcept { return std::forward<Self>(self).effectType_; }

    constexpr auto& state() & noexcept { return state_; }
    template <typename Self>
    constexpr auto state(this Self&& self) noexcept { return std::forward<Self>(self).state_; }

    constexpr auto& duration() & noexcept { return duration_; }
    template <typename Self>
    constexpr auto duration(this Self&& self) noexcept { return std::forward<Self>(self).duration_; }

    constexpr bool empty() const noexcept { return effectType_ == EffectType::None; }
    constexpr bool isActive() const noexcept { return state_ == EffectState::Active; }

    constexpr bool activate() noexcept;
    void timePass(Duration time = {}) noexcept;

private:
    EffectType effectType_{EffectType::None};
    Duration duration_{0, DurationType::Instant};
    EffectState state_{EffectState::Inactive};
    // std::vector<StatusModifier> statusMod_{};
};

inline constexpr bool Effect::activate() noexcept {
    if (state_ == EffectState::Inactive) {
        state_ = EffectState::Active;
        return true;
    }
    return false;
}

inline void Effect::timePass(Duration time) noexcept {
    if (duration_.timePass(time)) {
        state_ = EffectState::Finished;
    }
}
