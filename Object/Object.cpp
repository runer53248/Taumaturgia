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
template <Parameter param>
bool Object::checkGetParam() const {
    if (not can_get) {
        return false;
    }
    if constexpr (param == Parameter::Protection) {
        return can_defend;
    }
    if constexpr (param == Parameter::CureHealth) {
        return can_heal;
    }
    if constexpr (param == Parameter::Damage) {
        return can_attack;
    }
    if constexpr (param == Parameter::Health) {
        return can_alive;
    }
    if constexpr (param == Parameter::Restore) {
        return can_restore;
    }
    if constexpr (param == Parameter::Wear) {
        return can_wear;
    }
    return false;
}

template bool Object::checkGetParam<Parameter::Protection>() const;
template bool Object::checkGetParam<Parameter::CureHealth>() const;
template bool Object::checkGetParam<Parameter::Damage>() const;
template bool Object::checkGetParam<Parameter::Health>() const;
template bool Object::checkGetParam<Parameter::Restore>() const;
template bool Object::checkGetParam<Parameter::Wear>() const;
