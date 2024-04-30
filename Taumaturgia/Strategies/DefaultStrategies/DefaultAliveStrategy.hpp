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

#ifndef NO_PREMADE_STRATEGIES
constexpr std::optional<AliveStatus> AliveStrategy_<Default>::operator()(Livingable auto& obj) const {
    return default_alive_behavior(obj);
}
#else
constexpr std::optional<AliveStatus> UserStrategy_<Health, Default, std::optional<AliveStatus>>::operator()(Livingable auto& obj) const {
    return default_alive_behavior(obj);
}
#endif
