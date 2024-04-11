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

ActionStatus Object::attack(Object* owner, Object* target) const {
    return doAction(Actions::Attack, owner, target);
}
ActionStatus Object::defend(Object* owner, Object* target) const {
    return doAction(Actions::Defend, owner, target);
}
ActionStatus Object::wear(Object* owner, Object* target) const {
    return doAction(Actions::Wear, owner, target);
}
ActionStatus Object::heal(Object* owner, Object* target) const {
    return doAction(Actions::Heal, owner, target);
}
ActionStatus Object::restore(Object* owner, Object* target) const {
    return doAction(Actions::Restore, owner, target);
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
    return has.at(property);
}
