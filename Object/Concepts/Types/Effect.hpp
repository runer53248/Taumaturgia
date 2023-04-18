#pragma once
#include <stdexcept>
#include <vector>
#include "Duration.hpp"
#include "Enums/EffectState.hpp"
#include "Enums/EffectType.hpp"
#include "State.hpp"

// enum class EffectStatusModifier {
//     Suspended,
//     Delayed,
//     Removed
// };

// struct StatusModifier {
//     Duration duration{};
//     EffectStatusModifier status{EffectStatusModifier::Suspended};
// };

struct Effect {
    constexpr Effect() noexcept = default;
    constexpr Effect(EffectType attackEffect, Duration duration, State state) noexcept
        : effectType_{attackEffect}, duration_{duration}, state_{state} {}
    constexpr Effect(EffectType attackEffect, DurationType durationType) noexcept
        : Effect{attackEffect, Duration{1, durationType}, State{EffectState::Inactive}} {}
    constexpr Effect(EffectType attackEffect, Duration duration) noexcept
        : Effect{attackEffect, duration, State{EffectState::Inactive}} {}
    constexpr Effect(EffectType attackEffect, State state) noexcept
        : effectType_{attackEffect}, duration_{Duration{1, DurationType::Round}}, state_{state} {}
    constexpr explicit Effect(EffectType attackEffect) noexcept
        : effectType_{attackEffect} {}

    auto operator<=>(const Effect& other) const noexcept = default;
    bool operator==(const Effect& other) const noexcept = default;
    constexpr bool operator==(const EffectType& other) const noexcept {
        return effectType_ == other;
    }
    constexpr bool operator==(const EffectState& other) const noexcept {
        return state_ == State{other};
    }
    constexpr bool operator==(const State& other) const noexcept {
        return state_ == other;
    }
    constexpr bool operator==(const Duration& other) const noexcept {
        return duration_ == other;
    }

    auto& effectType() noexcept { return effectType_; }
    auto effectType() const noexcept { return effectType_; }

    auto& state() noexcept { return state_; }
    auto state() const noexcept { return state_; }

    auto& duration() noexcept { return duration_; }
    auto duration() const noexcept { return duration_; }

    bool isActive() const noexcept {
        return state_.effectState() == EffectState::Active;
    }

    bool activate() noexcept {
        if (state_.effectState() == EffectState::Inactive) {
            state_.effectState() = EffectState::Active;
            return true;
        }
        return false;
    }

    void timePass(Duration time = {}) noexcept {
        if (duration_.timePass(time)) {
            state_.end();
        }
    }

private:
    EffectType effectType_{EffectType::None};
    Duration duration_{0, DurationType::Instant};
    State state_{EffectState::Inactive};
    // std::vector<StatusModifier> statusMod_{};
};
