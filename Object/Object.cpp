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
        if (not can_defend) {
            return false;
        }
    }
    if constexpr (param == Parameter::CureHealth) {
        if (not can_heal) {
            return false;
        }
    }
    if constexpr (param == Parameter::Damage) {
        if (not can_attack) {
            return false;
        }
    }
    if constexpr (param == Parameter::Health) {
        if (not can_alive) {
            return false;
        }
    }
    if constexpr (param == Parameter::Restore) {
        if (not can_restore) {
            return false;
        }
    }
    if constexpr (param == Parameter::Wear) {
        if (not can_wear) {
            return false;
        }
    }
    return true;
}

template bool Object::checkGetParam<Parameter::Protection>() const;
template bool Object::checkGetParam<Parameter::CureHealth>() const;
template bool Object::checkGetParam<Parameter::Damage>() const;
template bool Object::checkGetParam<Parameter::Health>() const;
template bool Object::checkGetParam<Parameter::Restore>() const;
template bool Object::checkGetParam<Parameter::Wear>() const;
