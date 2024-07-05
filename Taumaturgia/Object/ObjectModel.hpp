#pragma once
#include "action_impl.hpp"

template <Namingable T>
constexpr Object::ObjectModel<T>::ObjectModel(const T& type)
    : type_{type}, commands_{action_impl::createCommands(type_)} {}

template <Namingable T>
constexpr std::string Object::ObjectModel<T>::name() const {
    return Namingable_trait::get(type_);
}

template <Namingable T>
constexpr std::optional<AliveStatus> Object::ObjectModel<T>::alive() const {
    return action_impl::alive(type_);
}

template <Namingable T>
constexpr ActionStatus Object::ObjectModel<T>::action(Actions action, Object* owner, Object* target) const {
    if (not commands_.contains(action)) {
        return ActionStatus::None;
    }
    return commands_.at(action)->execute(owner, target);
}

template <Namingable T>
constexpr auto Object::ObjectModel<T>::get(Properties param) -> optional_get_variant_type {
    return action_impl::get_impl(type_, param);
}

template <Namingable T>
constexpr auto Object::ObjectModel<T>::get(Properties param) const -> optional_get_variant_const_type {
    return action_impl::get_impl(type_, param);
}
