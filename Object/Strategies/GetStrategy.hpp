#pragma once
#include <concepts>
#include "../Concepts/Gettingable.hpp"
#include "../Concepts/Types/Enums/Parameter.hpp"
#include "../Concepts/Types/VariantType.hpp"

struct Default;
struct Object;

template <typename T>
struct GetStrategy_ {};

template <template<typename> typename Strategy, typename UserType>
concept GetStrategable = requires (Strategy<UserType> strategy, UserType& type, const UserType& ctype, Parameter param) {
	{strategy.template operator()<Parameter::Hp>(type)} -> std::same_as<get_optional_variant_type>;
	{strategy.template operator()<Parameter::Hp>(ctype)} -> std::same_as<get_optional_variant_const_type>;
};

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
