#include "Object.hpp"

std::string Object::name() const {
    return object_->name();
}
std::optional<AliveStatus> Object::alive() const {
    if (not hasProperty(Properties::Health)) {
        return {};
    }
    return object_->alive();
}

ActionStatus Object::doAction(Actions action, Object* owner, Object* target) const {
    if (not checkAction(action)) {
        return ActionStatus::None;
    }
    return object_->action(action, owner, target);
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

bool Object::checkAction(Actions action) const {
    const std::unordered_map<Actions, const Properties> action_to_parameter{
        {Actions::Heal, Properties::CureHealth},
        {Actions::Defend, Properties::Protection},
        {Actions::Attack, Properties::Damage},
        {Actions::Restore, Properties::Restore},
        {Actions::Wear, Properties::Wear}};

    if (not action_to_parameter.contains(action)) {
        return false;
    }
    return hasProperty(action_to_parameter.at(action));
}

bool Object::hasProperty(Properties property) const {
    return has_.at(property);
}
