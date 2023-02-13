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

using get_result_type = std::variant<std::monostate, std::reference_wrapper<AC>, std::reference_wrapper<Damage>, std::reference_wrapper<Hp>>;
using get_const_result_type = std::variant<std::monostate, std::reference_wrapper<const AC>, std::reference_wrapper<const Damage>, std::reference_wrapper<const Hp>>;

using optional_get_result_type = std::optional<get_result_type>;
using optional_get_const_result_type = std::optional<get_const_result_type>;

template <typename T>
concept GetResultable = 
	std::same_as<T, AC> ||
	std::same_as<T, Damage> ||
	std::same_as<T, Hp> ||
	std::same_as<T, const AC> ||
	std::same_as<T, const Damage> ||
	std::same_as<T, const Hp>;

template <GetResultable G>
const G& Get(const get_const_result_type& type) {
	return std::get<std::reference_wrapper<const G>>(type);
}

template <GetResultable G>
G& Get(const get_result_type& type) {
	return std::get<std::reference_wrapper<G>>(type);
}

template <template<typename> typename Strategy, typename UserType>
concept GetStrategable = requires (Strategy<UserType> strategy, UserType& type, const UserType& ctype, Parameter param) {
	{strategy.template operator()<Parameter::Hp>(type)} -> std::same_as<optional_get_result_type>;
	{strategy.template operator()<Parameter::Hp>(ctype)} -> std::same_as<optional_get_const_result_type>;
};

template <typename T>
concept Gettingable = Livingable<T> or Healingable<T> or Protectingable<T> or Damagingable<T>;

template <typename T>
using GetStrategy = std::conditional_t<
	Gettingable<T>,
	std::conditional_t<
		GetStrategable<GetStrategy_, T>,
		GetStrategy_<T>,
		GetStrategy_<Default> >,
	GetStrategy_<T> >;

template <> struct GetStrategy_<Default> {
	template <Parameter P>
	auto operator()(Gettingable auto& obj) const; // for const and non-const calls
};
