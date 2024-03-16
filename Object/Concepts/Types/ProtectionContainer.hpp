#pragma once
#include <array>
#include <optional>
#include "Protection.hpp"

struct ProtectionContainer {
    ProtectionContainer() noexcept = default;
    explicit ProtectionContainer(int baseValue) noexcept
        : globalArmor_{baseValue} {}

    friend constexpr auto operator<=>(const ProtectionContainer& lhs, const ProtectionContainer& rhs) noexcept = default;

    auto value() const& noexcept {
        return globalArmor_;
    }

    auto protectEffects() const& noexcept {
        return globalProtectEffects_;
    }

    std::vector<BodyLocation> getWearedLocations() const {
        std::vector<BodyLocation> result{};
        for (const auto& opt_protection : protections_) {
            if (opt_protection.has_value()) {
                result.push_back(opt_protection.value().location());
            }
        }
        return result;
    }

    auto& armorAtLocation(BodyLocation location) const& noexcept {
        return protections_.at(static_cast<size_t>(location));
    }
    auto& armorAtLocation(BodyLocation location) & noexcept {
        return protections_.at(static_cast<size_t>(location));
    }

    std::optional<Protection> wearProtection(const Protection& ac) & {
        std::optional<Protection> result = removeArmorAtLocation(ac.location());
        armorAtLocation(ac.location()) = ac;
        globalArmor_ += ac.armorClass();
        globalProtectEffects_.addEffectTypes(ac.protectEffects());
        return result;
    }

    std::optional<Protection> removeArmorAtLocation(BodyLocation location) & {
        if (auto result = armorAtLocation(location)) {
            armorAtLocation(location) = {};
            globalArmor_ -= result.value().armorClass();

            globalProtectEffects_.removeEffectTypes(result.value().protectEffects());
            for (auto opt_protection : protections_) {
                if (opt_protection) {
                    globalProtectEffects_.addEffectTypes(opt_protection.value().protectEffects());
                }
            }
            return result;
        }
        return {};
    }

private:
    std::array<std::optional<Protection>, static_cast<size_t>(BodyLocation::ALL)> protections_{};
    int globalArmor_{};
    EffectTypeContainer globalProtectEffects_{};
};
