#pragma once
#include <optional>
#include "Taumaturgia/Enums/AliveStatus.hpp"

inline std::optional<AliveStatus> default_alive_behavior(Livingable auto& obj) {
    auto hp = traits::accessHealth::get(obj).value();
    if (hp > 0) {
        return AliveStatus::Healthy;
    } else if (hp == 0) {
        return AliveStatus::Dying;
    }
    return AliveStatus::Death;
}

std::optional<AliveStatus> AliveStrategy_<Default>::operator()(Livingable auto& obj) const {
    return default_alive_behavior(obj);
}
