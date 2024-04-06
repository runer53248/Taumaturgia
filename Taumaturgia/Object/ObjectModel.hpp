#pragma once
#include "Action_impl.ipp"

template <Namingable T>
constexpr Object::ObjectModel<T>::ObjectModel(const T& type)
    : type_{type} {}

template <Namingable T>
constexpr std::string Object::ObjectModel<T>::name() const {
    return traits::accessName::get(type_);
}

template <Namingable T>
constexpr std::optional<AliveStatus> Object::ObjectModel<T>::alive() const {
    return action_impl::alive(type_);
}

template <Namingable T>
constexpr ActionStatus Object::ObjectModel<T>::action(Actions action, Object* owner, Object* target) const {
    return action_impl::action(action, type_, owner, target);
}

template <Namingable T>
constexpr auto Object::ObjectModel<T>::get(Parameter param) -> get_optional_variant_type {
    return action_impl::get_impl(type_, param);
}

template <Namingable T>
constexpr auto Object::ObjectModel<T>::get(Parameter param) const -> get_optional_variant_const_type {
    return action_impl::get_impl(type_, param);
}
