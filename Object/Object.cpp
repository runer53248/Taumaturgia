#include "Object.hpp"

std::string Object::name() const {
    return object_->name();
}
std::optional<AliveStatus> Object::alive() const {
    if (not can_alive) {
        return {};
    }
    return object_->alive();
}
ActionStatus Object::attack(Object* owner, Object* target) const {
    if (not can_attack) {
        return ActionStatus::None;
    }
    return object_->action(Actions::Attack, owner, target);
}
ActionStatus Object::defend(Object* owner, Object* target) const {
    if (not can_defend) {
        return ActionStatus::None;
    }
    return object_->action(Actions::Defend, owner, target);
}
ActionStatus Object::wear(Object* owner, Object* target) const {
    if (not can_wear) {
        return ActionStatus::None;
    }
    return object_->action(Actions::Wear, owner, target);
}
ActionStatus Object::heal(Object* owner, Object* target) const {
    if (not can_heal) {
        return ActionStatus::None;
    }
    return object_->action(Actions::Heal, owner, target);
}
ActionStatus Object::restore(Object* owner, Object* target) const {
    if (not can_restore) {
        return ActionStatus::None;
    }
    return object_->action(Actions::Restore, owner, target);
}

bool Object::checkGetParam(Parameter param) const {
    if (not can_get) {
        return false;
    }
    switch (param) {
    case Parameter::Health:
        return can_alive;
    case Parameter::CureHealth:
        return can_heal;
    case Parameter::Protection:
        return can_defend;
    case Parameter::Damage:
        return can_attack;
    case Parameter::Restore:
        return can_restore;
    case Parameter::Wear:
        return can_wear;
    default:
        return false;
    }
}
