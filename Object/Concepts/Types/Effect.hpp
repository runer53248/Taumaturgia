#pragma once

enum class AttackEffect {
    None,
    Slow,
    Paralyze,
    Stun,
    Daze,
    Dazzle,
    Sleep,
    Bleed,
    Burn,
    Shock,
    Freeze,
    Poison,
    Infection,
    Contagion,
    Smite,
    Devour,
    Petryfy
};

enum class DurationType : size_t {
    Instant = 0,
    Action = 1,
    Round = 2,
    Minute = 20,
    Hour = 1200,
    Day = 28'800
};

enum class EffectStatus {
    Inactive,
    Active,
    Removed,
    Ended
};

// enum class EffectStatusModifier {
//     Suspended,
//     Delayed,
//     Removed
// };

struct Duration {
    size_t value{1};
    DurationType type{DurationType::Round};

    auto operator<=>(const Duration& rhs) const = default;
};

struct EffectState {
    Duration duration{};
    EffectStatus status{EffectStatus::Inactive};

    auto operator<=>(const EffectState& rhs) const = default;
};

// struct StatusModifier {
//     Duration duration{};
//     EffectStatusModifier status{EffectStatusModifier::Suspended};
// };

struct Effect {
    Effect() = default;
    explicit Effect(AttackEffect effect) : effect_{effect}, state_{Duration{1, DurationType::Round}} {}
    Effect(AttackEffect effect, DurationType durationType) : effect_{effect}, state_{Duration{1, durationType}} {}
    Effect(AttackEffect effect, EffectState state) : effect_{effect}, state_{state} {}

    auto& effect() { return effect_; }
    auto effect() const { return effect_; }
    
    auto& status() { return state_.status; }
    auto status() const { return state_.status; }

    auto& duration() { return state_.duration; }
    auto duration() const { return state_.duration; }

    void activate() {
        if (state_.status == EffectStatus::Inactive) {
            state_.status = EffectStatus::Active;
        }
    }
    void timePass(Duration time = {}) {
        size_t time_left = static_cast<size_t>(state_.duration.type) * state_.duration.value;
        size_t time_pass = static_cast<size_t>(time.type) * time.value;

        if (time_pass >= time_left) {
            state_.duration.value = 0;
            state_.status = EffectStatus::Ended;
            return;
        }

        if (state_.duration.type == time.type) {
            state_.duration.value -= time.value;
            return;
        }

        time_left -= time_pass;
        if (time_left % static_cast<size_t>(DurationType::Day) == 0) {
            state_.duration.type = DurationType::Day;
            state_.duration.value = time_left / static_cast<size_t>(DurationType::Day);
            return;
        }
        if (time_left % static_cast<size_t>(DurationType::Hour) == 0) {
            state_.duration.type = DurationType::Hour;
            state_.duration.value = time_left / static_cast<size_t>(DurationType::Hour);
            return;
        }
        if (time_left % static_cast<size_t>(DurationType::Minute) == 0) {
            state_.duration.type = DurationType::Minute;
            state_.duration.value = time_left / static_cast<size_t>(DurationType::Minute);
            return;
        }
        if (time_left % static_cast<size_t>(DurationType::Round) == 0) {
            state_.duration.type = DurationType::Round;
            state_.duration.value = time_left / static_cast<size_t>(DurationType::Round);
            return;
        }
        if (time_left % static_cast<size_t>(DurationType::Action) == 0) {
            state_.duration.type = DurationType::Action;
            state_.duration.value = time_left / static_cast<size_t>(DurationType::Action);
            return;
        }
        throw std::logic_error("undefined effect duration.");
    }

    auto operator<=>(const Effect& rhs) const = default;
    auto operator==(const AttackEffect& rhs) const {
        return effect_ == rhs;
    }
    auto operator==(const EffectStatus& rhs) const {
        return state_.status == rhs;
    }

private:
    AttackEffect effect_{AttackEffect::None};
    EffectState state_{Duration{0, DurationType::Instant}};
    // std::vector<StatusModifier> statusMod_{};
};

// struct EffectContainer {

// private:
//     std::vector<Effect> effects_{};
// };

// struct Area{};
// struct WayPoint{};
// struct Encounter{};
// struct Trigger{};
// struct Hilites{};
// struct Placeable{
//     bool useable;
//     bool have_inventory;
//     bool have_trap;
//     bool have_lock;
// };
