#pragma once
#include <optional>
#include "Taumaturgia/Strategies/Enums/AliveStatus.hpp"

inline constexpr std::optional<AliveStatus> default_alive_behavior(Livingable auto& obj) {
    auto hp = Livingable_trait::get(obj).value();
    if (hp > 0) {
        return AliveStatus::Healthy;
    } else if (hp == 0) {
        return AliveStatus::Dying;
    }
    return AliveStatus::Death;
}
