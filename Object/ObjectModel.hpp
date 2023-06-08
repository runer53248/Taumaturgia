template <Namingable T>
std::string Object::ObjectModel<T>::name() const {
    return traits::accessName::get(type_);
}

template <Namingable T>
std::optional<bool> Object::ObjectModel<T>::alive() const {
    if constexpr (AliveStrategable<AliveStrategy, T>) {
        static constinit AliveStrategy<T> aliveStrategy_{};
        return aliveStrategy_(type_);
    }
    return {};
}

template <Namingable T>
bool Object::ObjectModel<T>::attack(Object* owner, Object* target) const {
    if constexpr (AttackStrategable<AttackStrategy, T>) {
        static constinit AttackStrategy<T> attackStrategy_{};
        return attackStrategy_(type_, owner, target);
    }
    return {};
}

template <Namingable T>
bool Object::ObjectModel<T>::defend(Object* owner, Object* target) const {
    if constexpr (DefendStrategable<DefendStrategy, T>) {
        static constinit DefendStrategy<T> defendStrategy_{};
        return defendStrategy_(type_, owner, target);
    }
    return {};
}

template <Namingable T>
bool Object::ObjectModel<T>::heal(Object* owner, Object* target) const {
    if constexpr (HealStrategable<HealStrategy, T>) {
        static constinit HealStrategy<T> healStrategy_{};
        return healStrategy_(type_, owner, target);
    }
    return {};
}

template <Namingable T>
bool Object::ObjectModel<T>::restore(Object* owner, Object* target) const {
    if constexpr (RestoreStrategable<RestoreStrategy, T>) {
        static constinit RestoreStrategy<T> restoreStrategy_{};
        return restoreStrategy_(type_, owner, target);
    }
    return {};
}

template <Namingable T>
constexpr auto Object::ObjectModel<T>::get(Parameter param) -> get_optional_variant_type {
    if constexpr (GetStrategable<GetStrategy, T>) {
        return get_impl(type_, param);
    }
    return {};
}

template <Namingable T>
constexpr auto Object::ObjectModel<T>::get(Parameter param) const -> get_optional_variant_const_type {
    if constexpr (GetStrategable<GetStrategy, T>) {
        return get_impl(type_, param);
    }
    return {};
}

template <Namingable T>
template <Parameter P, Gettingable G>
constexpr auto Object::ObjectModel<T>::get_impl(G& type) const {  // call const or non-const getStrategy_::operator() method depends on G constness
    static constinit GetStrategy<T> getStrategy_{};
    return std::invoke(&GetStrategy<T>::template operator()<P, G>, getStrategy_, type);
}

template <Namingable T>
constexpr auto Object::ObjectModel<T>::get_impl(Gettingable auto& type, Parameter param) const {
    using result_type = std::conditional_t<
        std::is_const_v<std::remove_reference_t<decltype(type)>>,
        get_optional_variant_const_type,
        get_optional_variant_type>;

    switch (param) {
    case Parameter::Protection:
        return get_impl<Parameter::Protection>(type);
    case Parameter::Damage:
        return get_impl<Parameter::Damage>(type);
    case Parameter::Health:
        return get_impl<Parameter::Health>(type);
    case Parameter::CureHealth:
        return get_impl<Parameter::CureHealth>(type);
    case Parameter::Restore:
        return get_impl<Parameter::Restore>(type);
    case Parameter::Wear:
        return get_impl<Parameter::Wear>(type);
    default:
        return result_type{};
    };
}
