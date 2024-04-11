#pragma once
#include <optional>
#include <variant>
#include "ArmorClass.hpp"
#include "Damage.hpp"
#include "Enums/EffectType.hpp"
#include "Enums/Properties.hpp"
#include "Health.hpp"
#include "WearContainer.hpp"

using get_variant_type = std::variant<std::monostate,
                                      std::reference_wrapper<Health>,
                                      std::reference_wrapper<CureHealth>,
                                      std::reference_wrapper<Damage>,
                                      std::reference_wrapper<Protection>,
                                      std::reference_wrapper<EffectTypeContainer>,
                                      std::reference_wrapper<WearContainer>>;
using get_variant_const_type = std::variant<std::monostate,
                                            std::reference_wrapper<const Health>,
                                            std::reference_wrapper<const CureHealth>,
                                            std::reference_wrapper<const Damage>,
                                            std::reference_wrapper<const Protection>,
                                            std::reference_wrapper<const EffectTypeContainer>,
                                            std::reference_wrapper<const WearContainer>>;

using optional_get_variant_type = std::optional<get_variant_type>;
using optional_get_variant_const_type = std::optional<get_variant_const_type>;

template <typename T>
concept is_optional_get_variant =
    std::same_as<std::remove_cvref_t<T>, optional_get_variant_type> or
    std::same_as<std::remove_cvref_t<T>, optional_get_variant_const_type>;

template <typename T, typename TYPE>
concept is_ref_type =
    std::same_as<std::remove_cvref_t<T>, std::reference_wrapper<TYPE>> or
    std::same_as<std::remove_cvref_t<T>, std::reference_wrapper<const TYPE>>;

namespace impl {

template <Properties P>
struct properties_to_type;

template <>
struct properties_to_type<Properties::Health> {
    using type = Health;
};

template <>
struct properties_to_type<Properties::CureHealth> {
    using type = CureHealth;
};

template <>
struct properties_to_type<Properties::Damage> {
    using type = Damage;
};

template <>
struct properties_to_type<Properties::Protection> {
    using type = Protection;
};

template <>
struct properties_to_type<Properties::Restore> {
    using type = EffectTypeContainer;
};
template <>
struct properties_to_type<Properties::Wear> {
    using type = WearContainer;
};

// TODO: check get type
// requires T is holded by opt_variant
template <typename TYPE>
constexpr decltype(auto) extract_optional_type(is_optional_get_variant auto&& opt_variant) {
    return opt_variant.transform([](auto&& var_ref) {
        using type = std::conditional_t<
            std::is_same_v<
                std::remove_cvref_t<decltype(var_ref)>,
                get_variant_const_type>,
            const TYPE,
            TYPE>;
        return std::get<std::reference_wrapper<type>>(std::move(var_ref));
    });
}

}  // namespace impl

template <Properties PROPERTY>
using properties_to_type = impl::properties_to_type<PROPERTY>::type;

template <Properties PROPERTY>
constexpr decltype(auto) extract_optional_type(is_optional_get_variant auto&& opt_variant) {
    return impl::extract_optional_type<properties_to_type<PROPERTY>>(opt_variant);
}
