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
