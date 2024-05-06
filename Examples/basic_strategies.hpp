#include "Taumaturgia/Object/Object.hpp"
#include "Taumaturgia/Properties/Properties.hpp"
#include "Taumaturgia/Strategies/DefaultStrategies/DefaultGetStrategy.hpp"
#include "Taumaturgia/Strategies/Enums/AliveStatus.hpp"

#ifndef NO_PREMADE_STRATEGIES
template <>
struct AliveStrategy_<Default> {
    constexpr std::optional<AliveStatus> operator()(Livingable auto&) const {
        return AliveStatus::Living;
    }
};
template <>
struct AttackStrategy_<Default> {
    constexpr ActionStatus operator()(Damagingable auto&, Object*, Object*) const {
        return ActionStatus::Success;
    }
};
template <>
struct DefendStrategy_<Default> {
    constexpr ActionStatus operator()(Protectingable auto&, Object*, Object*) const {
        return ActionStatus::Success;
    }
};
template <>
struct WearStrategy_<Default> {
    constexpr ActionStatus operator()(Wearingable auto&, Object*, Object*) const {
        return ActionStatus::Success;
    }
};
template <>
struct RestoreStrategy_<Default> {
    constexpr ActionStatus operator()(Restoringable auto&, Object*, Object*) const {
        return ActionStatus::Success;
    }
};
template <>
struct HealStrategy_<Default> {
    constexpr ActionStatus operator()(Healingable auto&, Object*, Object*) const {
        return ActionStatus::Success;
    }
};
#else

template <typename T>
struct UserStrategy_<T, Default, std::optional<AliveStatus> > {
    constexpr std::optional<AliveStatus> operator()(Livingable auto&) const {
        return AliveStatus::Living;
    }
};
template <typename T>
struct UserStrategy_<T, Default, ActionStatus> {
    constexpr ActionStatus operator()(auto&, Object*, Object*) const {
        return ActionStatus::Success;
    }
};

#endif
