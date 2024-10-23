#include "Object.hpp"

const std::unordered_map<Actions, const Properties> action_to_parameter{
    {Actions::Attack, Properties::Damage},
    {Actions::Defend, Properties::Protection},
    {Actions::Heal, Properties::CureHealth},
    {Actions::Restore, Properties::Restore},
    {Actions::Wear, Properties::Wear}};

std::string Object::name() const {
    return object_->name();
}
std::optional<AliveStatus> Object::alive() const {
    // if (not hasStrategyFor(Properties::Health)) {
    //     return {};
    // }
    return object_->alive();
}

ActionStatus Object::doAction(Actions action, Object* owner, Object* target) const {
    // if (not (action_to_parameter.contains(action) and hasStrategyFor(action_to_parameter.at(action)))) {
    //     return ActionStatus::None;
    // }
    return object_->action(action, owner, target);
}

bool Object::hasStrategyFor(Properties property) const {
    return have_strategy_for_.contains(property);
}

ActionStatus attack(const Object& object, Object* owner, Object* target) {
    return object.doAction(Actions::Attack, owner, target);
}
ActionStatus defend(const Object& object, Object* owner, Object* target) {
    return object.doAction(Actions::Defend, owner, target);
}
ActionStatus wear(const Object& object, Object* owner, Object* target) {
    return object.doAction(Actions::Wear, owner, target);
}
ActionStatus heal(const Object& object, Object* owner, Object* target) {
    return object.doAction(Actions::Heal, owner, target);
}
ActionStatus restore(const Object& object, Object* owner, Object* target) {
    return object.doAction(Actions::Restore, owner, target);
}
