#pragma once
#include <array>
#include <optional>
#include "Protection.hpp"

class WearContainer {
public:
    WearContainer() noexcept = default;
    explicit WearContainer(int baseValue) noexcept
        : globalArmor_{baseValue} {}

    friend std::strong_ordering operator<=>(const WearContainer& lhs, const WearContainer& rhs) noexcept = default;

    auto value() const& noexcept { return globalArmor_; }
    const auto& protectEffects() const& noexcept { return globalProtectEffects_; }

    std::vector<BodyLocation> getWearedLocations() const;

    template <typename Self>
    auto& armorAtLocation(this Self& self, BodyLocation location) noexcept { 
        return std::forward<Self>(self).protections_.at(static_cast<size_t>(location)); 
    }

    // return Protection removed from same location if existed
    std::optional<Protection> wearProtection(const Protection& ac) &;
    std::optional<Protection> removeArmorAtLocation(BodyLocation location) &;

private:
    std::array<std::optional<Protection>, static_cast<size_t>(BodyLocation::ALL)> protections_{};
    int globalArmor_{};
    EffectTypeContainer globalProtectEffects_{};
};

inline std::vector<BodyLocation> WearContainer::getWearedLocations() const {
    std::vector<BodyLocation> result{};
    for (const auto& opt_protection : protections_) {
        if (opt_protection.has_value()) {
            result.push_back(opt_protection.value().location());
        }
    }
    return result;
}

// return Protection removed from same location if existed
inline std::optional<Protection> WearContainer::wearProtection(const Protection& ac) & {
    BodyLocation changedLocation = ac.location();

    std::optional<Protection> result = removeArmorAtLocation(changedLocation);
    armorAtLocation(changedLocation) = ac;
    globalArmor_ += ac.armorClass();
    globalProtectEffects_.addEffectTypes(ac.protectEffects());
    return result;
}

inline std::optional<Protection> WearContainer::removeArmorAtLocation(BodyLocation location) & {
    auto opt_result = armorAtLocation(location);
    if (opt_result) {
        armorAtLocation(location) = Protection{};
        const auto& removed_armor = opt_result.value();
        globalArmor_ -= removed_armor.armorClass();

        globalProtectEffects_.removeEffectTypes(removed_armor.protectEffects());
        for (const auto& opt_protection : protections_) {
            if (opt_protection) {
                const auto& protection_at_location = opt_protection.value();
                globalProtectEffects_.addEffectTypes(protection_at_location.protectEffects());
            }
        }
    }
    return opt_result;
}
