#pragma once
#include <optional>
#include "Usage/Enums/AliveStatus.hpp"
#include "Usage/Traits.hpp"

inline constexpr std::optional<AliveStatus> default_alive_behavior(Livingable auto& obj) {
    auto hp = trait<Health>::get(obj).value();
    if (hp > 0) {
        return AliveStatus::Healthy;
    } else if (hp == 0) {
        return AliveStatus::Dying;
    }
    return AliveStatus::Death;
}
