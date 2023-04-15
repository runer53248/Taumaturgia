#pragma once
#include <variant>
#include <optional>
#include "AC.hpp"
#include "Damage.hpp"
#include "Hp.hpp"
#include "Enums/EffectType.hpp"

using get_variant_type = std::variant<std::monostate, 
	std::reference_wrapper<AC>, 
	std::reference_wrapper<Damage>, 
	std::reference_wrapper<Hp>,
	std::reference_wrapper<EffectTypeContainer>>;
using get_variant_const_type = std::variant<std::monostate, 
	std::reference_wrapper<const AC>, 
	std::reference_wrapper<const Damage>, 
	std::reference_wrapper<const Hp>,
	std::reference_wrapper<const EffectTypeContainer>>;

using optional_get_variant_type = std::optional<get_variant_type>;
using optional_get_variant_const_type = std::optional<get_variant_const_type>;