#pragma once
#include <algorithm>
#include <iterator>  // std::inserter
#include <set>
#include "Enums/EffectType.hpp"

class EffectTypeContainer {
public:
    template <typename T>
    using container_type = std::set<T>;

    EffectTypeContainer() noexcept = default;

    EffectTypeContainer(std::initializer_list<EffectType> effectTypes) noexcept
        : effectTypes_{effectTypes} {}

    EffectTypeContainer(EffectType effectType) noexcept
        : effectTypes_{effectType} {}

    std::strong_ordering operator<=>(const EffectTypeContainer&) const noexcept = default;

    auto begin() noexcept { return effectTypes_.begin(); }
    auto end() noexcept { return effectTypes_.end(); }
    auto cbegin() const noexcept { return effectTypes_.begin(); }
    auto cend() const noexcept { return effectTypes_.end(); }
    auto begin() const noexcept { return effectTypes_.begin(); }
    auto end() const noexcept { return effectTypes_.end(); }

    bool contains(const EffectType& type) const noexcept { return effectTypes_.contains(type); }
    bool empty() const noexcept { return effectTypes_.empty(); }

    auto& effectTypes() & noexcept { return effectTypes_; }
    auto effectTypes() && noexcept { return effectTypes_; }
    auto& effectTypes() const& noexcept { return effectTypes_; }
    auto effectTypes() const&& noexcept { return effectTypes_; }

    void addEffectType(const EffectType& type) { effectTypes_.insert(type); }
    void addEffectTypes(const EffectTypeContainer& types) { effectTypes_.insert(types.cbegin(), types.cend()); }

    void removeEffectType(const EffectType& type) { effectTypes_.erase(type); }
    void removeEffectTypes(const EffectTypeContainer& types);

private:
    container_type<EffectType> effectTypes_{};
};

inline void EffectTypeContainer::removeEffectTypes(const EffectTypeContainer& types) {
    container_type<EffectType> result;
    std::set_difference(
        effectTypes_.begin(),
        effectTypes_.end(),
        types.effectTypes_.begin(),
        types.effectTypes_.end(),
        std::inserter(result, result.end()));
    effectTypes_ = result;
}
