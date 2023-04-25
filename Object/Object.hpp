#pragma once
#include <concepts>
#include <memory>
#include <optional>
#include "Concepts/Namingable.hpp"
#include "Strategies/Strategies.hpp"

#include <experimental/propagate_const>
#include <functional>

class Object;

template <typename T>
concept Objected = std::same_as<T, Object> or std::same_as<T, const Object>;

class Object {
private:
    struct ObjectConcept {
        virtual ~ObjectConcept() = default;

        virtual std::string name() const = 0;
        virtual std::optional<bool> alive() const = 0;
        virtual bool attack(Object* owner, Object* targe) const = 0;
        virtual bool defend(Object* owner, Object* target) const = 0;
        virtual bool heal(Object* owner, Object* target) const = 0;
        virtual bool restore(Object* owner, Object* target) const = 0;
        virtual constexpr get_optional_variant_type get(Parameter param) = 0;
        virtual constexpr get_optional_variant_const_type get(Parameter param) const = 0;
    };

    template <Namingable T>
    struct ObjectModel : ObjectConcept {
    public:
        ObjectModel(const T& type)
            : type_{type} {}
        ~ObjectModel() override = default;

        std::string name() const override;
        std::optional<bool> alive() const override;
        bool attack(Object* owner, Object* target) const override;
        bool defend(Object* owner, Object* target) const override;
        bool heal(Object* owner, Object* target) const override;
        bool restore(Object* owner, Object* target) const override;
        constexpr get_optional_variant_type get(Parameter param) override;
        constexpr get_optional_variant_const_type get(Parameter param) const override;

    private:
        template <Parameter P, Gettingable G>
        inline constexpr auto get_impl(G& type) const;
        inline constexpr auto get_impl(Gettingable auto& type, Parameter param) const;

        T type_;
    };

    std::experimental::propagate_const<std::unique_ptr<ObjectConcept>> object_;

public:
    const bool can_alive{};
    const bool can_attack{};
    const bool can_defend{};
    const bool can_heal{};
    const bool can_restore{};
    const bool can_wear{};
    const bool can_get{};

    template <Namingable T>
    Object(const T& obj)
        : object_{std::make_unique<ObjectModel<T>>(obj)},
          can_alive{AliveStrategable<AliveStrategy, T>},
          can_attack{AttackStrategable<AttackStrategy, T>},
          can_defend{DefendStrategable<DefendStrategy, T>},
          can_heal{HealStrategable<HealStrategy, T>},
          can_restore{RestoreStrategable<RestoreStrategy, T>},
          can_wear{WearStrategable<WearStrategy, T>},
          can_get{GetStrategable<GetStrategy, T>} {}

    std::string name() const {
        return object_->name();
    }
    std::optional<bool> alive() const {
        if (not can_alive) {
            return {};
        }
        return object_->alive();
    }
    bool attack(Object* owner, Object* target = nullptr) const {
        if (not can_attack) {
            return false;
        }
        return object_->attack(owner, target);
    }
    bool defend(Object* owner, Object* target = nullptr) const {
        if (not can_defend) {
            return false;
        }
        return object_->defend(owner, target);
    }
    bool heal(Object* owner, Object* target = nullptr) const {
        if (not can_heal) {
            return false;
        }
        return object_->heal(owner, target);
    }
    bool restore(Object* owner, Object* target = nullptr) const {
        if (not can_restore) {
            return false;
        }
        return object_->restore(owner, target);
    }

    template <Parameter param>
    friend constexpr auto getOptVariant(Objected auto& object) -> decltype(object.object_->get(std::declval<Parameter>())) {  // return type depends on object constness
        if (not object.can_get) {
            return {};
        }

        if constexpr (param == Parameter::Protection) {
            if (not object.can_defend) {
                return {};
            }
        } else if constexpr (param == Parameter::CureHealth) {
            if (not object.can_heal) {
                return {};
            }
        } else if constexpr (param == Parameter::Damage) {
            if (not object.can_attack) {
                return {};
            }
        } else if constexpr (param == Parameter::Health) {
            if (not object.can_alive) {
                return {};
            }
        } else if constexpr (param == Parameter::Restore) {
            if (not object.can_restore) {
                return {};
            }
        } else if constexpr (param == Parameter::Wear) {
            if (not object.can_wear) {
                return {};
            }
        }
        return object.object_->get(param);
    }

    template <Parameter param, Objected T>
    friend constexpr auto getOpt(T& object) {
        auto opt_variant = getOptVariant<param>(object);

        if constexpr (param == Parameter::Health or param == Parameter::CureHealth) {
            using type = std::conditional_t<std::is_const_v<std::remove_reference_t<decltype(object)>>,
                                            const Health, Health>;
            using return_type = std::reference_wrapper<type>;

            return opt_variant.transform([](auto var_ref) {  // transform variant of reference_wrapper to reference_wrapper of type
                return std::get<return_type>(var_ref);
            });

        } else if constexpr (param == Parameter::Damage) {
            using type = std::conditional_t<std::is_const_v<std::remove_reference_t<decltype(object)>>,
                                            const Damage, Damage>;
            using return_type = std::reference_wrapper<type>;

            return opt_variant.transform([](auto var_ref) {
                return std::get<return_type>(var_ref);
            });
        } else if constexpr (param == Parameter::Protection) {
            using type = std::conditional_t<std::is_const_v<std::remove_reference_t<decltype(object)>>,
                                            const Protection, Protection>;
            using return_type = std::reference_wrapper<type>;

            return opt_variant.transform([](auto var_ref) {
                return std::get<return_type>(var_ref);
            });
        } else if constexpr (param == Parameter::Restore) {
            using type = std::conditional_t<std::is_const_v<std::remove_reference_t<decltype(object)>>,
                                            const EffectTypeContainer, EffectTypeContainer>;
            using return_type = std::reference_wrapper<type>;

            return opt_variant.transform([](auto var_ref) {
                return std::get<return_type>(var_ref);
            });
        } else if constexpr (param == Parameter::Wear) {
            using type = std::conditional_t<std::is_const_v<std::remove_reference_t<decltype(object)>>,
                                            const ProtectionContainer, ProtectionContainer>;
            using return_type = std::reference_wrapper<type>;

            return opt_variant.transform([](auto var_ref) {
                return std::get<return_type>(var_ref);
            });
        }
    }
};

template <Namingable T>
std::string Object::ObjectModel<T>::name() const {
    return type_.name;
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
