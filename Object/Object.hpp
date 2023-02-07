#pragma once
#include <memory>
#include <optional>
#include <concepts>
#include "Concepts/Namingable.hpp"
#include "Strategies/Strategies.hpp"

class Object {
private:
	struct ObjectConcept {
		virtual ~ObjectConcept() = default;

		virtual std::string name() const = 0;
		virtual std::optional<bool> alive() const = 0;
		virtual bool attack(Object* owner, Object* target = nullptr) = 0;
		virtual bool defend(Object* owner, Object* target = nullptr) = 0;
		virtual bool heal(int amount, Object* owner, Object* target = nullptr) = 0;
        virtual std::optional<get_result_type> get(Parameter param) = 0;
	};

	template <Namingable T>
	struct ObjectModel : ObjectConcept {
	public:
		ObjectModel(const T& type) : type_{type} {}
		~ObjectModel() override = default;
		
		std::string name() const override;
		std::optional<bool> alive() const override;
		bool attack(Object* owner, Object* target) override;
		bool defend(Object* owner, Object* target) override;
		bool heal(int amount, Object* owner, Object* target) override;
        std::optional<get_result_type> get(Parameter param) override;

	private:
		T type_;
		AliveStrategy<T> aliveStrategy_{};
		AttackStrategy<T> attackStrategy_{};
		DefendStrategy<T> defendStrategy_{};
		HealStrategy<T> healStrategy_{};
        GetStrategy<T> getStrategy_{};
	};

   	std::unique_ptr<ObjectConcept> object_;

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
	std::optional<bool> alive() {
		if (not can_alive) { return {}; }
        return object_->alive();
    }
    bool attack(Object *owner, Object *target = nullptr) {
		if (not can_attack) { return false; }
        return object_->attack(owner, target);
    }
    bool defend(Object *owner, Object *target = nullptr) {
		if (not can_defend) { return false; }
        return object_->defend(owner, target);
    }
    bool heal(int amount, Object *owner, Object *target = nullptr) {
		if (not can_heal) { return false; }
        return object_->heal(amount, owner, target);
    }
    std::optional<get_result_type> get(Parameter param) {
		if (not can_get) { return {}; }
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
bool Object::ObjectModel<T>::attack(Object* owner, Object* target) {
    if constexpr (AttackStrategable< AttackStrategy, T>) {
        return attackStrategy_(type_, owner, target);
    }
    return false;
}

template <Namingable T>
bool Object::ObjectModel<T>::defend(Object* owner, Object* target) {
    if constexpr (DefendStrategable< DefendStrategy, T>) {
        return defendStrategy_(type_, owner, target);
    }
    return false;
}

template <Namingable T>
bool Object::ObjectModel<T>::heal(int amount, Object* owner, Object* target) {
    if constexpr (HealStrategable< HealStrategy, T>) {
        return healStrategy_(type_, amount, owner, target);
    }
    return false;
}

template <Namingable T>
std::optional<get_result_type> Object::ObjectModel<T>::get(Parameter param) {
    if constexpr (GetStrategable< GetStrategy, T>) {
        switch (param) {
            case Parameter::Ac:
                return getStrategy_.template operator()<Parameter::Ac>(type_);
            case Parameter::Damage:
                return getStrategy_.template operator()<Parameter::Damage>(type_);
            case Parameter::Hp:
                return getStrategy_.template operator()<Parameter::Hp>(type_);
            case Parameter::CureHp:
                return getStrategy_.template operator()<Parameter::CureHp>(type_);
        };
    }
    return {};
}

inline Object* Whom(Object *const owner, Object *const target) {
    if ((owner == target) or not target) {
        return owner;
    }
    return target;
}

std::optional<bool> AliveStrategy_<Default>::operator()(Livingable auto &obj) const {
    return obj.hp.value() > 0;
}

bool AttackStrategy_<Default>::operator()(Damagingable auto &obj, Object *owner, Object *target) {
    if (not owner) {
        return false;
    }
    auto *suspect = Whom(owner, target);
    auto is_success = suspect->get(Parameter::Hp)
        .and_then([&](auto&& variant) {
            Hp& value_ref = std::get<std::reference_wrapper<Hp>>(variant);
            value_ref.value() -= obj.dmg.value();
            return std::optional{value_ref};
        });
    return is_success.has_value();
}

bool DefendStrategy_<Default>::operator()(Protectingable auto &obj, Object *owner, Object *target) {
    if (not owner) {
        return false;
    }
    auto *suspect = Whom(owner, target);
    auto is_success = suspect->get(Parameter::Ac)
        .and_then([&](auto&& variant) {
            AC& ac_ref = std::get<std::reference_wrapper<AC>>(variant);
            ac_ref.value(obj.ac.location()) = obj.ac.value();
            return std::optional{variant};
        });
    return true;
}

bool HealStrategy_<Default>::operator()(Healingable auto &obj, int amount, Object *owner, Object *target) {
    if (not owner) {
        return false;
    }
    auto *suspect = Whom(owner, target);
    auto is_success = suspect->get(Parameter::Hp)
        .and_then([&](auto&& variant) {
            Hp& value_ref = std::get<std::reference_wrapper<Hp>>(variant);
            value_ref.value() += obj.cureHp.value();
            return std::optional{value_ref};
        });
    return is_success.has_value();
}

template <Parameter P>
std::optional<get_result_type> GetStrategy_<Default>::operator()(Getable auto &obj) {
    using type = std::remove_reference_t<decltype(obj)>;
    if constexpr (P == Parameter::Hp) {
        if constexpr (Livingable<type>) {
            return std::ref(obj.hp);
        }
    }
    if constexpr (P == Parameter::CureHp) {
        if constexpr (Healingable<type>) {
            return std::ref(obj.cureHp);
        }
    }
    if constexpr (P == Parameter::Ac) {
        if constexpr (Protectingable<type>) {
            return std::ref(obj.ac);
        }
    }
    if constexpr (P == Parameter::Damage) {
        if constexpr (Damagingable<type>) {
            return std::ref(obj.dmg);
        }
    }
    return {};
}
