#include "Taumaturgia/Object/Object.hpp"
#include "Taumaturgia/Strategies/Defaults/DefaultGetterStrategy.hpp"
#include "Usage/Enums/AliveStatus.hpp"

#ifdef NO_PREMADE_STRATEGIES

template <typename TYPE>
struct UserStrategy_<TYPE, Default> {
    static constexpr std::optional<AliveStatus> operator()(Livingable auto&) {
        return AliveStatus::Living;
    }

    static constexpr ActionStatus operator()(auto&, Object*, Object*) {
        return ActionStatus::Success;
    }
};

#else

template <>
struct AliveStrategy_<Default> {
    static constexpr std::optional<AliveStatus> operator()(Livingable auto&) {
        return AliveStatus::Living;
    }
};
template <>
struct AttackStrategy_<Default> {
    static constexpr ActionStatus operator()(Damagingable auto&, Object*, Object*) {
        return ActionStatus::Success;
    }
};
template <>
struct DefendStrategy_<Default> {
    static constexpr ActionStatus operator()(Protectingable auto&, Object*, Object*) {
        return ActionStatus::Success;
    }
};
template <>
struct WearStrategy_<Default> {
    static constexpr ActionStatus operator()(Wearingable auto&, Object*, Object*) {
        return ActionStatus::Success;
    }
};
template <>
struct RestoreStrategy_<Default> {
    static constexpr ActionStatus operator()(Restoringable auto&, Object*, Object*) {
        return ActionStatus::Success;
    }
};
template <>
struct HealStrategy_<Default> {
    static constexpr ActionStatus operator()(Healingable auto&, Object*, Object*) {
        return ActionStatus::Success;
    }
};

#endif
