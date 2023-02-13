#pragma once
#include <memory>
#include <optional>
#include <concepts>
#include "Concepts/Namingable.hpp"
#include "Strategies/Strategies.hpp"

#include <experimental/propagate_const>
#include <functional>

class Object {
private:
	struct ObjectConcept {
        using optional_get_result = optional_get_result_type;
        using optional_get_const_result = optional_get_const_result_type;

		virtual ~ObjectConcept() = default;

		virtual std::string name() const = 0;
		virtual std::optional<bool> alive() const = 0;
		virtual bool attack(Object* owner, Object* target = nullptr) const = 0;
		virtual bool defend(Object* owner, Object* target = nullptr) const = 0;
		virtual bool heal(Object* owner, Object* target = nullptr) const = 0;
        virtual optional_get_result get(Parameter param) = 0;
        virtual optional_get_const_result get(Parameter param) const = 0;
	};

	template <Namingable T>
	struct ObjectModel : ObjectConcept {
	public:
		ObjectModel(const T& type) : type_{type} {}
		~ObjectModel() override = default;
		
		std::string name() const override;
		std::optional<bool> alive() const override;
		bool attack(Object* owner, Object* target) const override;
		bool defend(Object* owner, Object* target) const override;
		bool heal(Object* owner, Object* target) const override;
        optional_get_result get(Parameter param) override;
        optional_get_const_result get(Parameter param) const override;

	private:
        template <Parameter P, Gettingable G>
        inline constexpr auto get_impl(G& type) const;
        inline auto get_impl(Gettingable auto& type, Parameter param) const;

		T type_;
	};

   	std::experimental::propagate_const<std::unique_ptr<ObjectConcept>> object_;

public:
	const bool can_alive{};
	const bool can_attack{};
	const bool can_defend{};
	const bool can_heal{};
	const bool can_get{};

	template <Namingable T> 
	Object(const T& obj) : 
		object_{std::make_unique<ObjectModel<T>>(obj)},
		can_alive{AliveStrategable<AliveStrategy, T>},
		can_attack{AttackStrategable<AttackStrategy, T>},
		can_defend{DefendStrategable<DefendStrategy, T>},
		can_heal{HealStrategable<HealStrategy, T>},
		can_get{GetStrategable<GetStrategy, T>} {}

	std::string name() const { 
		return object_->name();
	}
	std::optional<bool> alive() const {
		if (not can_alive) { return {}; }
        return object_->alive();
    }
    bool attack(Object *owner, Object *target = nullptr) const {
		if (not can_attack) { return false; }
        return object_->attack(owner, target);
    }
    bool defend(Object *owner, Object *target = nullptr) const {
		if (not can_defend) { return false; }
        return object_->defend(owner, target);
    }
    bool heal(Object *owner, Object *target = nullptr) const {
		if (not can_heal) { return false; }
        return object_->heal(owner, target);
    }

    friend auto get(auto &object, Parameter param) -> decltype(object.object_->get(std::declval<Parameter>())) { // return type depends on object constness
        if (not object.can_get) { return {}; }

        if (param == Parameter::Ac && not object.can_defend) { return {}; }
        if (param == Parameter::CureHp && not object.can_heal) { return {}; }
        if (param == Parameter::Damage && not object.can_attack) { return {}; }
        if (param == Parameter::Hp && not object.can_alive) { return {}; }

        return object.object_->get(param);
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
auto Object::ObjectModel<T>::get(Parameter param) -> optional_get_result {
    if constexpr (GetStrategable<GetStrategy, T>) {
        return get_impl(type_, param);
    }
    return {};
}

template <Namingable T>
auto Object::ObjectModel<T>::get(Parameter param) const -> optional_get_const_result {
    if constexpr (GetStrategable<GetStrategy, T>) {
        return get_impl(type_, param);
    }
    return {};
}

template<Namingable T>
template<Parameter P, Gettingable G>
constexpr auto Object::ObjectModel<T>::get_impl(G& type) const { // call const or non-const getStrategy_::operator() method depends on G constness
    static constinit GetStrategy<T> getStrategy_{};
    return std::invoke(&GetStrategy<T>::template operator()<P, G>, getStrategy_, type);
}

template<Namingable T>
auto Object::ObjectModel<T>::get_impl(Gettingable auto& type, Parameter param) const {
    using result_type = std::conditional_t<
        std::is_const_v<std::remove_reference_t<decltype(type)>>,
        optional_get_const_result,
        optional_get_result>;

    switch (param) { 
        case Parameter::Ac:
            return get_impl<Parameter::Ac>(type);
        case Parameter::Damage:
            return get_impl<Parameter::Damage>(type);
        case Parameter::Hp:
            return get_impl<Parameter::Hp>(type);
        case Parameter::CureHp:
            return get_impl<Parameter::CureHp>(type);
        default:
            return result_type{}; 
    };
}
