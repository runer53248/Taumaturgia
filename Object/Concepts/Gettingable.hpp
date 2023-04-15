#pragma once
#include <type_traits>
#include "Livingable.hpp"
#include "Healingable.hpp"
#include "Protectingable.hpp"
#include "Damagingable.hpp"
#include "Restoringable.hpp"
#include "Types/Enums/Parameter.hpp"
#include "Types/VariantType.hpp"

#include "Types/EffectTypeContainer.hpp"

template <typename T>
concept GetResultable = 
	std::same_as<T, AC>
	or std::same_as<T, Damage>
	or std::same_as<T, Hp>
	or std::same_as<T, EffectTypeContainer>
	or std::same_as<T, const AC>
	or std::same_as<T, const Damage>
	or std::same_as<T, const Hp>
	or std::same_as<T, const EffectTypeContainer>;

template <GetResultable G>
const G& Get(const get_variant_const_type& type) {
	return std::get<std::reference_wrapper<const G>>(type);
}

template <GetResultable G>
G& Get(const get_variant_type& type) {
	return std::get<std::reference_wrapper<G>>(type);
}

template <typename T>
concept Gettingable = Damagingable<T> 
	or Healingable<T> 
    or Livingable<T> 
	or Protectingable<T> 
	or Restoringable<T>;
