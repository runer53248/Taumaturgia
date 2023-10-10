#pragma once
#include <optional>
#include <variant>
#include "ArmorClass.hpp"
#include "Damage.hpp"
#include "Enums/EffectType.hpp"
#include "Enums/Parameter.hpp"
#include "Health.hpp"
#include "ProtectionContainer.hpp"

using get_variant_type = std::variant<std::monostate,
                                      std::reference_wrapper<Health>,
                                      std::reference_wrapper<CureHealth>,
                                      std::reference_wrapper<Damage>,
                                      std::reference_wrapper<Protection>,
                                      std::reference_wrapper<EffectTypeContainer>,
                                      std::reference_wrapper<ProtectionContainer>>;
using get_variant_const_type = std::variant<std::monostate,
                                            std::reference_wrapper<const Health>,
                                            std::reference_wrapper<const CureHealth>,
                                            std::reference_wrapper<const Damage>,
                                            std::reference_wrapper<const Protection>,
                                            std::reference_wrapper<const EffectTypeContainer>,
                                            std::reference_wrapper<const ProtectionContainer>>;

using get_optional_variant_type = std::optional<get_variant_type>;
using get_optional_variant_const_type = std::optional<get_variant_const_type>;

template <typename T>
concept GetOptVarianted =
    std::same_as<std::remove_cvref_t<T>, get_optional_variant_type> or
    std::same_as<std::remove_cvref_t<T>, get_optional_variant_const_type>;

template <typename T>
constexpr auto extract_to_opt_ref_wrapper(GetOptVarianted auto&& opt_variant) {
    return opt_variant.transform([](auto&& var_ref) {
        using type = std::conditional_t<
            std::is_same_v<std::remove_cvref_t<decltype(var_ref)>, get_variant_const_type>,
            const T,
            T>;
        return std::get<std::reference_wrapper<type>>(std::move(var_ref));
    });
}

template <Parameter param>
constexpr auto get_opt_ref_wrapper(GetOptVarianted auto&& opt_variant) {
    if constexpr (param == Parameter::Health) {
        return extract_to_opt_ref_wrapper<Health>(opt_variant);
    }
    if constexpr (param == Parameter::CureHealth) {
        return extract_to_opt_ref_wrapper<CureHealth>(opt_variant);
    }
    if constexpr (param == Parameter::Damage) {
        return extract_to_opt_ref_wrapper<Damage>(opt_variant);
    }
    if constexpr (param == Parameter::Protection) {
        return extract_to_opt_ref_wrapper<Protection>(opt_variant);
    }
    if constexpr (param == Parameter::Restore) {
        return extract_to_opt_ref_wrapper<EffectTypeContainer>(opt_variant);
    }
    if constexpr (param == Parameter::Wear) {
        return extract_to_opt_ref_wrapper<ProtectionContainer>(opt_variant);
    }
}
