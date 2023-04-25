#pragma once
#include <optional>
#include <variant>
#include "ArmorClass.hpp"
#include "Damage.hpp"
#include "Enums/EffectType.hpp"
#include "Health.hpp"
#include "ProtectionContainer.hpp"

using get_variant_type = std::variant<std::monostate,
                                      std::reference_wrapper<Protection>,
                                      std::reference_wrapper<ProtectionContainer>,
                                      std::reference_wrapper<Damage>,
                                      std::reference_wrapper<Health>,
                                      std::reference_wrapper<EffectTypeContainer>>;
using get_variant_const_type = std::variant<std::monostate,
                                            std::reference_wrapper<const Protection>,
                                            std::reference_wrapper<const ProtectionContainer>,
                                            std::reference_wrapper<const Damage>,
                                            std::reference_wrapper<const Health>,
                                            std::reference_wrapper<const EffectTypeContainer>>;

using get_optional_variant_type = std::optional<get_variant_type>;
using get_optional_variant_const_type = std::optional<get_variant_const_type>;