#include "Taumaturgia/Object/Object.hpp"
#include "Taumaturgia/Properties/Properties.hpp"
#include "Taumaturgia/Strategies/DefaultStrategies/DefaultGetStrategy.hpp"
#include "Taumaturgia/Strategies/Enums/AliveStatus.hpp"

#ifndef NO_PREMADE_STRATEGIES
constexpr std::optional<AliveStatus> AliveStrategy_<Default>::operator()(Livingable auto&) const {
    return AliveStatus::Living;
}
constexpr ActionStatus AttackStrategy_<Default>::operator()(Damagingable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
constexpr ActionStatus DefendStrategy_<Default>::operator()(Protectingable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
constexpr ActionStatus WearStrategy_<Default>::operator()(Wearingable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
constexpr ActionStatus RestoreStrategy_<Default>::operator()(Restoringable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
constexpr ActionStatus HealStrategy_<Default>::operator()(Healingable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
#else
constexpr std::optional<AliveStatus> UserStrategy_<Health, Default, std::optional<AliveStatus>>::operator()(Livingable auto&) const {
    return AliveStatus::Living;
}
constexpr ActionStatus UserStrategy_<Damage, Default, ActionStatus>::operator()(Damagingable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
constexpr ActionStatus UserStrategy_<Protection, Default, ActionStatus>::operator()(Protectingable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
constexpr ActionStatus UserStrategy_<WearContainer, Default, ActionStatus>::operator()(Wearingable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
constexpr ActionStatus UserStrategy_<EffectTypeContainer, Default, ActionStatus>::operator()(Restoringable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
constexpr ActionStatus UserStrategy_<CureHealth, Default, ActionStatus>::operator()(Healingable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
#endif
