#pragma once
#include <memory>
#include <optional>
#include <concepts>
#include "Concepts/Namingable.hpp"
#include "Strategies/Strategies.hpp"

#include <experimental/propagate_const>

class Object {
private:
	struct ObjectConcept {
		virtual ~ObjectConcept() = default;

		virtual std::string name() const = 0;
		virtual std::optional<bool> alive() const = 0;
		virtual bool attack(Object* owner, Object* target = nullptr) const = 0;
		virtual bool defend(Object* owner, Object* target = nullptr) const = 0;
		virtual bool heal(int amount, Object* owner, Object* target = nullptr) const = 0;
        virtual std::optional<get_result_type> get(Parameter param) = 0;
        virtual std::optional<get_const_result_type> get(Parameter param) const = 0;
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
		bool heal(int amount, Object* owner, Object* target) const override;
        std::optional<get_result_type> get(Parameter param) override;
        std::optional<get_const_result_type> get(Parameter param) const override;

	private:
		T type_;
		static constexpr AliveStrategy<T> aliveStrategy_{};
		static constexpr AttackStrategy<T> attackStrategy_{};
		static constexpr DefendStrategy<T> defendStrategy_{};
		static constexpr HealStrategy<T> healStrategy_{};
        static constexpr GetStrategy<T> getStrategy_{};

        auto get(Getable auto& type, Parameter param) const {
            using result_type = std::conditional_t<
                std::is_const_v<std::remove_reference_t<decltype(type)>>,
                std::optional<get_const_result_type>,
                std::optional<get_result_type> >;

            switch (param) {
                case Parameter::Ac:
                    return getStrategy_.template operator()<Parameter::Ac>(type);
                case Parameter::Damage:
                    return getStrategy_.template operator()<Parameter::Damage>(type);
                case Parameter::Hp:
                    return getStrategy_.template operator()<Parameter::Hp>(type);
                case Parameter::CureHp:
                    return getStrategy_.template operator()<Parameter::CureHp>(type);
            };
            return result_type{};
        }
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
    bool heal(int amount, Object *owner, Object *target = nullptr) const {
		if (not can_heal) { return false; }
        return object_->heal(amount, owner, target);
    }
    auto get(Parameter param) -> decltype(object_->get(std::declval<Parameter>())) {
		if (not can_get) { return {}; }

        if (param == Parameter::Ac && not can_defend) { return {}; }
        if (param == Parameter::CureHp && not can_heal) { return {}; }
        if (param == Parameter::Damage && not can_attack) { return {}; }
        if (param == Parameter::Hp && not can_alive) { return {}; }

        return object_->get(param);
    }
    auto get(Parameter param) const -> decltype(object_->get(std::declval<Parameter>())) {
		if (not can_get) { return {}; }

        if (param == Parameter::Ac && not can_defend) { return {}; }
        if (param == Parameter::CureHp && not can_heal) { return {}; }
        if (param == Parameter::Damage && not can_attack) { return {}; }
        if (param == Parameter::Hp && not can_alive) { return {}; }

        return object_->get(param);
    }
};

template <Namingable T>
std::string Object::ObjectModel<T>::name() const { 
    return type_.name; 
}

template <Namingable T>
std::optional<bool> Object::ObjectModel<T>::alive() const {
    if constexpr (AliveStrategable< AliveStrategy, T>) {
        return aliveStrategy_(type_);
    }
    return {};
}

template <Namingable T>
bool Object::ObjectModel<T>::attack(Object* owner, Object* target) const {
    if constexpr (AttackStrategable< AttackStrategy, T>) {
        return attackStrategy_(type_, owner, target);
    }
    return false;
}

template <Namingable T>
bool Object::ObjectModel<T>::defend(Object* owner, Object* target) const {
    if constexpr (DefendStrategable< DefendStrategy, T>) {
        return defendStrategy_(type_, owner, target);
    }
    return false;
}

template <Namingable T>
bool Object::ObjectModel<T>::heal(int amount, Object* owner, Object* target) const {
    if constexpr (HealStrategable< HealStrategy, T>) {
        return healStrategy_(type_, amount, owner, target);
    }
    return false;
}

template <Namingable T>
std::optional<get_result_type> Object::ObjectModel<T>::get(Parameter param) {
    if constexpr (GetStrategable< GetStrategy, T>) {
        return get(type_, param);
    }
    return {};
}

template <Namingable T>
std::optional<get_const_result_type> Object::ObjectModel<T>::get(Parameter param) const {
    if constexpr (GetStrategable< GetStrategy, T>) {
        return get(type_, param);
    }
    return {};
}
