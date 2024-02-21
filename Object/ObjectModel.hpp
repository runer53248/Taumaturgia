#pragma once

class Object::Action_impl {
public:
    static constexpr ActionStatus attack(Namingable auto const& type, Object* owner, Object* target);
    static constexpr ActionStatus defend(Namingable auto const& type, Object* owner, Object* target);
    static constexpr ActionStatus heal(Namingable auto const& type, Object* owner, Object* target);
    static constexpr ActionStatus restore(Namingable auto const& type, Object* owner, Object* target);
    static constexpr auto get_impl(Gettingable auto& type, Parameter param);
};

template <Namingable T>
constexpr ActionStatus Object::Action_impl::attack(const T& type, Object* owner, Object* target) {
    if constexpr (AttackStrategable<AttackStrategy, T>) {
        static constinit AttackStrategy<T> attackStrategy_{};
        return attackStrategy_(type, owner, target);
    }
    return ActionStatus::None;
}

template <Namingable T>
constexpr ActionStatus Object::Action_impl::defend(const T& type, Object* owner, Object* target) {
    if constexpr (DefendStrategable<DefendStrategy, T>) {
        static constinit DefendStrategy<T> defendStrategy_{};
        return defendStrategy_(type, owner, target);
    }
    return ActionStatus::None;
}

template <Namingable T>
constexpr ActionStatus Object::Action_impl::heal(const T& type, Object* owner, Object* target) {
    if constexpr (HealStrategable<HealStrategy, T>) {
        static constinit HealStrategy<T> healStrategy_{};
        return healStrategy_(type, owner, target);
    }
    return ActionStatus::None;
}

template <Namingable T>
constexpr ActionStatus Object::Action_impl::restore(const T& type, Object* owner, Object* target) {
    if constexpr (RestoreStrategable<RestoreStrategy, T>) {
        static constinit RestoreStrategy<T> restoreStrategy_{};
        return restoreStrategy_(type, owner, target);
    }
    return ActionStatus::None;
}

template <Gettingable G>
constexpr auto Object::Action_impl::get_impl(G& type, Parameter param) {
    using result_type = std::conditional_t<
        std::is_const_v<std::remove_reference_t<decltype(type)>>,
        get_optional_variant_const_type,
        get_optional_variant_type>;

    static constinit GetStrategy<G> getStrategy_{};

    switch (param) {
    case Parameter::Protection:
        return std::invoke(&GetStrategy<G>::template operator()<Parameter::Protection, G>, getStrategy_, type);
    case Parameter::Damage:
        return std::invoke(&GetStrategy<G>::template operator()<Parameter::Damage, G>, getStrategy_, type);
    case Parameter::Health:
        return std::invoke(&GetStrategy<G>::template operator()<Parameter::Health, G>, getStrategy_, type);
    case Parameter::CureHealth:
        return std::invoke(&GetStrategy<G>::template operator()<Parameter::CureHealth, G>, getStrategy_, type);
    case Parameter::Restore:
        return std::invoke(&GetStrategy<G>::template operator()<Parameter::Restore, G>, getStrategy_, type);
    case Parameter::Wear:
        return std::invoke(&GetStrategy<G>::template operator()<Parameter::Wear, G>, getStrategy_, type);
    default:
        return result_type{};
    };
}

template <Namingable T>
constexpr Object::ObjectModel<T>::ObjectModel(const T& type)
    : type_{type} {}

template <Namingable T>
constexpr std::string Object::ObjectModel<T>::name() const {
    return traits::accessName::get(type_);
}

template <Namingable T>
constexpr std::optional<AliveStatus> Object::ObjectModel<T>::alive() const {
    if constexpr (AliveStrategable<AliveStrategy, T>) {
        static constinit AliveStrategy<T> aliveStrategy_{};
        return aliveStrategy_(type_);
    }
    return {};
}

template <Namingable T>
constexpr ActionStatus Object::ObjectModel<T>::action(Actions action, Object* owner, Object* target) const {
    switch (action) {
    case Actions::Attack:
        return Action_impl::attack(type_, owner, target);
    case Actions::Defend:
        return Action_impl::defend(type_, owner, target);
    case Actions::Heal:
        return Action_impl::heal(type_, owner, target);
    case Actions::Restore:
        return Action_impl::restore(type_, owner, target);
    }
    return ActionStatus::None;
}

template <Namingable T>
constexpr auto Object::ObjectModel<T>::get(Parameter param) -> get_optional_variant_type {
    if constexpr (GetStrategable<GetStrategy, T>) {
        return Action_impl::get_impl(type_, param);
    }
    return {};
}

template <Namingable T>
constexpr auto Object::ObjectModel<T>::get(Parameter param) const -> get_optional_variant_const_type {
    if constexpr (GetStrategable<GetStrategy, T>) {
        return Action_impl::get_impl(type_, param);
    }
    return {};
}
