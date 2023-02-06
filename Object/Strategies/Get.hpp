#pragma once
#include <concepts>
#include <optional>
#include <variant>
#include "../Concepts/Livingable.hpp"
#include "../Concepts/Healingable.hpp"
#include "../Concepts/Protectingable.hpp"
#include "../Concepts/Damagingable.hpp"

enum class Parameter {
    Hp,
	CureHp,
	Ac,
	Damage
};

struct Default;
struct Object;

template <typename T>
struct GetStrategy_ {};

using get_result_type = std::variant<int *const, std::reference_wrapper<AC>>;

template <template<typename> typename Strategy, typename UserType>
concept GetStrategable = requires (Strategy<UserType> strategy, UserType& type, Parameter param) {
	{strategy.template operator()<Parameter::Hp>(type)} -> std::same_as<std::optional<get_result_type>>;
};

template <typename T>
concept Getable = Livingable<T> or Healingable<T> or Protectingable<T> or Damagingable<T>;

template <typename T>
using GetStrategy = std::conditional_t<
	Getable<T>,
	std::conditional_t<
		GetStrategable<GetStrategy_, T>,
		GetStrategy_<T>,
		GetStrategy_<Default> >,
	GetStrategy_<T> >;

template <> struct GetStrategy_<Default> {
	template<Parameter P>
	std::optional<get_result_type> operator()(Getable auto &obj);
};
