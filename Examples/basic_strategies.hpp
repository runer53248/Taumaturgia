#include "Object/Object.hpp"
#include "Object/Properties/Properties.hpp"
#include "Object/Strategies/DefaultStrategies/DefaultGetStrategy.hpp"

std::optional<AliveStatus> AliveStrategy_<Default>::operator()(Livingable auto&) const {
    return AliveStatus::Living;
}
#ifndef NO_PREMADE_STRATEGIES
ActionStatus AttackStrategy_<Default>::operator()(Damagingable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
ActionStatus DefendStrategy_<Default>::operator()(Protectingable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
ActionStatus WearStrategy_<Default>::operator()(Wearingable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
ActionStatus RestoreStrategy_<Default>::operator()(Restoringable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
ActionStatus HealStrategy_<Default>::operator()(Healingable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
#else
ActionStatus UserStrategy_<Damage, Default>::operator()(Damagingable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
ActionStatus UserStrategy_<Protection, Default>::operator()(Protectingable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
ActionStatus UserStrategy_<WearContainer, Default>::operator()(Wearingable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
ActionStatus UserStrategy_<EffectTypeContainer, Default>::operator()(Restoringable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
ActionStatus UserStrategy_<CureHealth, Default>::operator()(Healingable auto&, Object*, Object*) const {
    return ActionStatus::Success;
}
#endif
