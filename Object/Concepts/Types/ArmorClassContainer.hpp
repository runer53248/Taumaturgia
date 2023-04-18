#pragma once
#include <array>
#include <optional>
#include "ArmorClass.hpp"

struct ArmorClassContainer {
    ArmorClassContainer() noexcept = default;
    explicit ArmorClassContainer(int baseValue) noexcept
        : globalArmor_{baseValue} {}

    auto value() const& {
        return globalArmor_;
    }

    auto protectEffects() const& {
        return globalProtectEffects_;
    }

    std::vector<BodyLocation> getWearedLocations() const {
        std::vector<BodyLocation> result{};
        for (const auto& loc : values_) {
            if (loc.has_value()) {
                result.push_back(loc.value().location());
            }
        }
        return result;
    }

    auto& armorAtLocation(BodyLocation location) const& {
        return values_.at(static_cast<size_t>(location));
    }
    auto& armorAtLocation(BodyLocation location) & {
        return values_.at(static_cast<size_t>(location));
    }

    std::optional<ArmorClass> wearArmor(const ArmorClass& ac) & {
        std::optional<ArmorClass> result = removeArmorAtLocation(ac.location());
        armorAtLocation(ac.location()) = ac;
        globalArmor_ += ac.value();
        globalProtectEffects_.addEffectTypes(ac.protectEffects());
        return result;
    }

    std::optional<ArmorClass> removeArmorAtLocation(BodyLocation location) & {
        if (auto result = armorAtLocation(location)) {
            armorAtLocation(location) = {};
            globalArmor_ -= result.value().value();

            globalProtectEffects_.removeEffectTypes(result.value().protectEffects());
            for (auto opt_ac : values_) {
                if (opt_ac) {
                    globalProtectEffects_.addEffectTypes(opt_ac.value().protectEffects());
                }
            }
            return result;
        }
        return {};
    }

private:
    std::array<std::optional<ArmorClass>, static_cast<size_t>(BodyLocation::ALL)> values_{};
    int globalArmor_{};
    EffectTypeContainer globalProtectEffects_{};
};
