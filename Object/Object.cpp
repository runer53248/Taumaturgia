#include "Object.hpp"

std::string Object::name() const {
    return object_->name();
}
std::optional<bool> Object::alive() const {
    if (not can_alive) {
        return {};
    }
    return object_->alive();
}
bool Object::attack(Object* owner, Object* target) const {
    if (not can_attack) {
        return false;
    }
    return object_->attack(owner, target);
}
bool Object::defend(Object* owner, Object* target) const {
    if (not can_defend) {
        return false;
    }
    return object_->defend(owner, target);
}
bool Object::heal(Object* owner, Object* target) const {
    if (not can_heal) {
        return false;
    }
    return object_->heal(owner, target);
}
bool Object::restore(Object* owner, Object* target) const {
    if (not can_restore) {
        return false;
    }
    return object_->restore(owner, target);
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
