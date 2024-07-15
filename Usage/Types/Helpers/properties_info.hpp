#pragma once
#include "Usage/Enums/Properties.hpp"
// #include "Usage/Traits.hpp"

namespace impl {

template <Properties P>
struct properties_info;

template <>
struct properties_info<Properties::Health> {
    using type = Health;
    using trait = trait<Health>;
};

template <>
struct properties_info<Properties::CureHealth> {
    using type = CureHealth;
    using trait = trait<CureHealth>;

    template <typename T>
    using strategy = HealStrategy<T>;
};

template <>
struct properties_info<Properties::Damage> {
    using type = Damage;
    using trait = trait<Damage>;

    template <typename T>
    using strategy = AttackStrategy<T>;
};

template <>
struct properties_info<Properties::Protection> {
    using type = Protection;
    using trait = trait<Protection>;

    template <typename T>
    using strategy = DefendStrategy<T>;
};

template <>
struct properties_info<Properties::Restore> {
    using type = EffectTypeContainer;
    using trait = trait<EffectTypeContainer>;

    template <typename T>
    using strategy = RestoreStrategy<T>;
};
template <>
struct properties_info<Properties::Wear> {
    using type = WearContainer;
    using trait = trait<WearContainer>;

    template <typename T>
    using strategy = WearStrategy<T>;
};

template <>
struct properties_info<Properties::Name> {
    using type = Name;
    using trait = trait<Name>;
};

}  // namespace impl

template <Properties PROPERTY>
using properties_type = impl::properties_info<PROPERTY>::type;

template <Properties PROPERTY>
using properties_trait = impl::properties_info<PROPERTY>::trait;

template <Properties PROPERTY, typename T>
concept is_properties_accessable = properties_trait<PROPERTY>::template accessable<std::remove_reference_t<T>>;

template <typename T>
using add_optional_ref_wrapper = std::optional<std::reference_wrapper<T>>;

template <Properties PROPERTY, bool IS_CONST = false>
using get_result_type = add_optional_ref_wrapper<
    std::conditional_t<
        IS_CONST,
        const properties_type<PROPERTY>,
        properties_type<PROPERTY>>>;
