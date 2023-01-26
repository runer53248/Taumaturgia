#pragma once
#include <memory>
#include <iostream>
#include <optional>
#include <concepts>

enum class Parameter {
    Hp
};

class Object;

template<typename Strategy, typename UserType>
concept AttackStrategable = requires (Strategy strategy, UserType& type, Object* owner, Object* target) { 
	{strategy.operator()(type, owner, target)} -> std::same_as<bool>;
	{strategy.operator()()} -> std::same_as<bool>;
};

template<typename Strategy, typename UserType>
concept DefendStrategable = requires (Strategy strategy, UserType& type, Object* owner, Object* target) { 
	{strategy.operator()(type, owner, target)} -> std::same_as<bool>;
	{strategy.operator()()} -> std::same_as<bool>;
};

template<typename Strategy, typename UserType>
concept HealStrategable = requires (Strategy strategy, UserType& type, int amount, Object* owner, Object* target) { 
	{strategy.operator()(type, amount, owner, target)} -> std::same_as<bool>;
	{strategy.operator()()} -> std::same_as<bool>;
};

template<typename Strategy, typename UserType>
concept GetStrategable = requires (Strategy strategy, UserType& type, Parameter param) { 
	{strategy.operator()(type, param)} -> std::same_as<std::optional<int*const>>;
	{strategy.operator()()} -> std::same_as<bool>;
};

class Object {
private:
	struct ObjectConcept {
		virtual ~ObjectConcept() {}

		virtual std::string name() const = 0;

		virtual bool attack(Object* owner, Object* target = nullptr) = 0;
		virtual bool defend(Object* owner, Object* target = nullptr) = 0;
		virtual bool heal(int amount, Object* owner, Object* target = nullptr) = 0;
        virtual std::optional<int*const> get(Parameter param) = 0;
	};

	template<typename T, 
			AttackStrategable<T> ATTACK_STRATEGY,
			DefendStrategable<T> DEFEND_STRATEGY,
			HealStrategable<T> HEAL_STRATEGY,
            GetStrategable<T> GET_STRATEGY> 
	struct ObjectModel : ObjectConcept {
	public:
		ObjectModel(const T& type);
		~ObjectModel() override = default;
		
		std::string name() const override;

		bool attack(Object* owner, Object* target) override;
		bool defend(Object* owner, Object* target) override;
		bool heal(int amount, Object* owner, Object* target) override;
        std::optional<int*const> get(Parameter param) override;

	private:
		T type;
		ATTACK_STRATEGY attackFunc{};
		DEFEND_STRATEGY defendFunc{};
		HEAL_STRATEGY healFunc{};
        GET_STRATEGY getFunc{};
	};

   	std::shared_ptr<ObjectConcept> object;

public:
	template<typename T> struct Attack;
	template<typename T> struct Defend;
	template<typename T> struct Heal;
    template<typename T> struct Get;

	template<typename T, 
			AttackStrategable<T> ATTACK_STRATEGY = Attack<T>,
			DefendStrategable<T> DEFEND_STRATEGY = Defend<T>,
			HealStrategable<T> HEAL_STRATEGY = Heal<T>,
			GetStrategable<T> GET_STRATEGY = Get<T>> 
	Object( const T& obj, 
			ATTACK_STRATEGY atack = ATTACK_STRATEGY{}, 
			DEFEND_STRATEGY defend = DEFEND_STRATEGY{}, 
			HEAL_STRATEGY heal = HEAL_STRATEGY{},
            GET_STRATEGY get = GET_STRATEGY{}) : 
		object( new ObjectModel<T, ATTACK_STRATEGY, DEFEND_STRATEGY, HEAL_STRATEGY, GET_STRATEGY>( obj ) ) {}

	std::string name() const { 
		return object->name();
	}

    bool attack(Object* owner, auto... args) {
        return object->attack(owner, std::forward<decltype(args)>(args)...);
    }
    bool defend(auto... args) {
        return object->defend(std::forward<decltype(args)>(args)...);
    }
    bool heal(int amount, Object* owner, auto... args) {
        return object->heal(amount, owner, std::forward<decltype(args)>(args)...);
    }
    std::optional<int*const> get(Parameter param) {
        return object->get(param);
    }

	friend bool attack(const Object& obj,Object* owner,  auto... args) {
		return obj.object->attack(owner, std::forward<decltype(args)>(args)...);
	}
	friend bool defend(const Object& obj, auto... args) {
		return obj.object->defend(std::forward<decltype(args)>(args)...); 
	}
	friend bool heal(const Object& obj, int amount, Object* owner, auto... args) {
		return obj.object->heal(amount, owner, std::forward<decltype(args)>(args)...); 
	}
    friend std::optional<int*const> get(const Object& obj, Parameter param) {
        return obj.object->get(param);
    }
};
