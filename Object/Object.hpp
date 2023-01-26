#pragma once
#include <memory>
#include <optional>
#include <concepts>

enum class Parameter;
class Object;

template<typename T>
concept Nameable = requires (T t) { 
	{t.name} -> std::convertible_to<std::string>;
};

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

template<class T>
concept Strategable = AttackStrategable<Attack<T>, T> && DefendStrategable<Defend<T>, T> && HealStrategable<Heal<T>, T> && GetStrategable<Get<T>, T>;

template<typename T> struct Attack;
template<typename T> struct Defend;
template<typename T> struct Heal;
template<typename T> struct Get;

class Object {
private:
	struct ObjectConcept {
		virtual ~ObjectConcept() = default;

		virtual std::string name() const = 0;

		virtual bool attack(Object* owner, Object* target = nullptr) = 0;
		virtual bool defend(Object* owner, Object* target = nullptr) = 0;
		virtual bool heal(int amount, Object* owner, Object* target = nullptr) = 0;
        virtual std::optional<int*const> get(Parameter param) = 0;
	};

	template<Nameable T> 
	requires Strategable<T>
	struct ObjectModel : ObjectConcept {
	public:
		ObjectModel(const T& type) : type( type ) {}
		~ObjectModel() override = default;
		
		std::string name() const override;

		bool attack(Object* owner, Object* target) override;
		bool defend(Object* owner, Object* target) override;
		bool heal(int amount, Object* owner, Object* target) override;
        std::optional<int*const> get(Parameter param) override;

	private:
		T type;
		Attack<T> attackFunc{};
		Defend<T> defendFunc{};
		Heal<T> healFunc{};
        Get<T> getFunc{};
	};

   	std::shared_ptr<ObjectConcept> object;

public:
	template<Nameable T> 
	Object(const T& obj) : 
		object( new ObjectModel<T>( obj ) ) {}

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
