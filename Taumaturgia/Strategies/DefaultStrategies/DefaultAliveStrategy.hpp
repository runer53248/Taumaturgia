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

template <>
#ifdef NO_PREMADE_STRATEGIES
struct UserStrategy_<Health, Default, std::optional<AliveStatus> > {
#else
struct AliveStrategy_<Default> {
#endif
    constexpr std::optional<AliveStatus> operator()(Livingable auto& obj) const {
        return default_alive_behavior(obj);
    }
};
