#pragma once
#include "Usage/Enums/Properties.hpp"

namespace impl {

template <Properties P>
struct properties_info;

template <>
struct properties_info<Properties::Health> {
    using type = Health;
    using trait = Livingable_trait;
};

template <>
struct properties_info<Properties::CureHealth> {
    using type = CureHealth;
    using trait = Healingable_trait;
};

template <>
struct properties_info<Properties::Damage> {
    using type = Damage;
    using trait = Damagingable_trait;
};

template <>
struct properties_info<Properties::Protection> {
    using type = Protection;
    using trait = Protectingable_trait;
};

template <>
struct properties_info<Properties::Restore> {
    using type = EffectTypeContainer;
    using trait = Restoringable_trait;
};
template <>
struct properties_info<Properties::Wear> {
    using type = WearContainer;
    using trait = Wearingable_trait;
};

}  // namespace impl

template <Properties PROPERTY>
using properties_type = impl::properties_info<PROPERTY>::type;

template <Properties PROPERTY>
using properties_trait = impl::properties_info<PROPERTY>::trait;

template <Properties PROPERTY, typename T>
concept is_properties_accessable = traits::helpers::trait_accessable<std::remove_reference_t<T>,
                                                                     properties_trait<PROPERTY>,
                                                                     properties_type<PROPERTY>>;

template <Properties PROPERTY, typename T>
using get_result_type = std::optional<std::reference_wrapper<
    std::conditional_t<
        std::is_const_v<T>,
        const properties_type<PROPERTY>,
        properties_type<PROPERTY>>>>;
