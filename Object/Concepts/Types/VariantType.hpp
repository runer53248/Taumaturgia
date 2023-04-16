#pragma once
#include <variant>
#include <optional>
#include "ArmorClass.hpp"
#include "ArmorClassContainer.hpp"
#include "Damage.hpp"
#include "Health.hpp"
#include "Enums/EffectType.hpp"

using get_variant_type = std::variant<std::monostate,
	std::reference_wrapper<ArmorClass>,
	std::reference_wrapper<ArmorClassContainer>,
	std::reference_wrapper<Damage>,
	std::reference_wrapper<Health>,
	std::reference_wrapper<EffectTypeContainer>>;
using get_variant_const_type = std::variant<std::monostate,
	std::reference_wrapper<const ArmorClass>,
	std::reference_wrapper<const ArmorClassContainer>,
	std::reference_wrapper<const Damage>,
	std::reference_wrapper<const Health>,
	std::reference_wrapper<const EffectTypeContainer>>;

using get_optional_variant_type = std::optional<get_variant_type>;
using get_optional_variant_const_type = std::optional<get_variant_const_type>;