#pragma once
#include <set>
#include <algorithm>
#include "Enums/EffectType.hpp"

struct EffectTypeContainer {
    template <typename T>
    using container_type = std::set<T>;

    EffectTypeContainer() = default;
    EffectTypeContainer(const EffectType& effectType) : effectTypes_{effectType} {}
    EffectTypeContainer(const EffectTypeContainer& effectTypes) : effectTypes_{effectTypes.effectTypes_} {}
    EffectTypeContainer(std::initializer_list<EffectType> effectTypes) : effectTypes_{effectTypes} {}

    auto operator<=>(const EffectTypeContainer&) const = default;

    auto begin() { return effectTypes_.begin(); }
    auto end() { return effectTypes_.end(); }
    auto cbegin() const { return effectTypes_.begin(); }
    auto cend() const { return effectTypes_.end(); }
    auto begin() const { return effectTypes_.begin(); }
    auto end() const { return effectTypes_.end(); }

    bool contains(const EffectType& type) const {
        return effectTypes_.contains(type);
    }

    bool empty() const noexcept {
        return effectTypes_.empty();
    }

    auto& effectTypes() & noexcept { return effectTypes_; }
    auto effectTypes() && noexcept { return effectTypes_; }
    auto& effectTypes() const & noexcept { return effectTypes_; }
    auto effectTypes() const && noexcept { return effectTypes_; }

    void addEffectType(const EffectType& type) {
        effectTypes_.insert(type);
    }
    void addEffectTypes(const EffectTypeContainer& types) {
        effectTypes_.insert(types.cbegin(), types.cend());
    }

    void removeEffectType(const EffectType& type) {
        effectTypes_.erase(type);
    }
    void removeEffectTypes(const EffectTypeContainer& types) {
        container_type<EffectType> result;
        std::set_difference(effectTypes_.begin(), effectTypes_.end(), types.effectTypes_.begin(), types.effectTypes_.end(), inserter(result, result.end()));
        effectTypes_ = result;
    }

private:
    container_type<EffectType> effectTypes_{};
};
