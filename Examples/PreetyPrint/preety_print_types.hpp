#pragma once
#include <format>
#include <sstream>

#include "Usage/Traits.hpp"

#include "PrintActionStatus.hpp"
#include "PrintAliveStatus.hpp"
#include "PrintBodyLocation.hpp"
#include "PrintCureHealth.hpp"
#include "PrintDamage.hpp"
#include "PrintDamageType.hpp"
#include "PrintDamagingable.hpp"
#include "PrintDuration.hpp"
#include "PrintEffectContainer.hpp"
#include "PrintEffectState.hpp"
#include "PrintEffectType.hpp"
#include "PrintEffectTypeContainer.hpp"
#include "PrintHealth.hpp"
#include "PrintName.hpp"
#include "PrintProtection.hpp"
#include "PrintWearContainer.hpp"
#include "Redirect.hpp"

template <typename T, typename... TYPES>
concept preety_printed = (std::same_as<T, TYPES> or ...);

template <
    preety_printed<
        ActionStatus,
        AliveStatus,
        BodyLocation,
        CureHealth,
        Damage,
        DamageType,
        Duration,
        EffectContainer,
        EffectState,
        EffectType,
        EffectTypeContainer,
        Health,
        Name,
        Protection,
        WearContainer> T>
struct std::formatter<T> : std::formatter<std::string> {
    auto format(const T& t, [[maybe_unused]] std::format_context& ctx) const {
        std::ostringstream o;
        o << t;
        return formatter<string>::format(std::move(o).str(), ctx);
        // return std::ranges::copy(std::move(o).str(), ctx.out()).out;
    }
};