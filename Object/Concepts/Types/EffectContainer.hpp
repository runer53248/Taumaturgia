#pragma once
#include <algorithm>
#include <set>
#include <vector>
#include "Effect.hpp"

struct EffectContainer {
    template <typename T>
    using container_type = std::vector<T>;

    constexpr EffectContainer() = default;
    constexpr EffectContainer(const Effect& effect)
        : effects_{effect} {}
    constexpr EffectContainer(std::initializer_list<Effect> effects)
        : effects_{effects} {}

    auto operator<=>(const EffectContainer&) const = default;

    auto begin() { return effects_.begin(); }
    auto end() { return effects_.end(); }
    auto cbegin() const { return effects_.begin(); }
    auto cend() const { return effects_.end(); }
    auto begin() const { return effects_.begin(); }
    auto end() const { return effects_.end(); }

    bool empty() const noexcept {
        return effects_.empty();
    }

    auto& effects() & { return effects_; }
    auto effects() && { return effects_; }  // don't return reference from temporary objects
    auto& effects() const& { return effects_; }
    auto effects() const&& { return effects_; }

    bool isEffectType(const Effect& effect) const {
        return std::ranges::find(effects_, effect) != effects_.end();
    }

    void addEffectType(const Effect& effect) {
        effects_.push_back(effect);
    }
    void addEffectTypes(const container_type<Effect>& effects) {
        for (const auto& effect : effects) {
            effects_.push_back(effect);
        }
    }

    void removeEffectType(const EffectType& effectType) {
        auto it = std::ranges::find_if(effects_, [effectType](const Effect& effect) {
            return effect.effectType() == effectType;
        });
        if (it != effects_.end()) {
            effects_.erase(it);
        }
    }

private:
    container_type<Effect> effects_{};
};
