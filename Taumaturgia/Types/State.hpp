#pragma once
#include "Enums/EffectState.hpp"

struct State {
    constexpr State() noexcept = default;
    constexpr explicit State(EffectState state) noexcept
        : state_{state} {}

    constexpr auto operator<=>(const State& other) const noexcept = default;

    auto& effectState() & noexcept { return state_; }
    auto effectState() && noexcept { return state_; }
    auto effectState() const& noexcept { return state_; }
    auto effectState() const&& noexcept { return state_; }

    void deactivate() noexcept { state_ = EffectState::Inactive; }
    void activate() noexcept { state_ = EffectState::Active; }
    void remove() noexcept { state_ = EffectState::Removed; }
    void end() noexcept { state_ = EffectState::Ended; }

private:
    EffectState state_{EffectState::Inactive};
};