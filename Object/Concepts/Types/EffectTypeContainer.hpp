#pragma once
#include <set>
#include <algorithm>
#include "Enums/EffectType.hpp"

struct EffectTypeContainer {
    template <typename T>
    using container_type = std::set<T>;

    EffectTypeContainer() = default;
    EffectTypeContainer(const EffectType& type) : effectTypes_{type} {}
    EffectTypeContainer(const container_type<EffectType>& effectTypes) : effectTypes_{effectTypes} {}
    EffectTypeContainer(std::initializer_list<EffectType> types) : effectTypes_{types} {}

    auto operator<=>(const EffectTypeContainer&) const = default;

    auto begin() { return effectTypes_.begin(); }
    auto end() { return effectTypes_.end(); }
    auto cbegin() const { return effectTypes_.begin(); }
    auto cend() const { return effectTypes_.end(); }
    auto begin() const { return effectTypes_.begin(); }
    auto end() const { return effectTypes_.end(); }

    auto& effectTypes() & noexcept { return effectTypes_; }
    auto effectTypes() && noexcept { return effectTypes_; }
    auto& effectTypes() const & noexcept { return effectTypes_; }
    auto effectTypes() const && noexcept { return effectTypes_; }

    bool isEffectType(const EffectType& effectType) const {
        return effectTypes_.contains(effectType);
    }

    void addEffectType(const EffectType& effectType) {
        effectTypes_.insert(effectType);
    }
    void addEffectTypes(const container_type<EffectType>& effectTypes) {
        effectTypes_.insert(effectTypes.cbegin(), effectTypes.cend());
    }

    void removeEffectType(const EffectType& effectType) {
        effectTypes_.erase(effectType);
    }
    void removeEffectTypes(const container_type<EffectType>& effectTypes) {
        container_type<EffectType> result;
        std::set_difference(effectTypes_.begin(), effectTypes_.end(), effectTypes.begin(), effectTypes.end(), inserter(result, result.end()));
        effectTypes_ = result;
    }

private:
    container_type<EffectType> effectTypes_{};
};
