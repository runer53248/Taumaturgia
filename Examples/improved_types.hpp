#pragma once
#include "Taumaturgia/Properties/Properties.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

#ifndef NO_PREMADE_PROPERTIES
template <typename T>
using Damaging_impl = impl::Damaging_<T>;
#else
namespace impl {
constinit char damaging_type_name[] = "Damaging";
}
template <typename T>
using Damaging_impl = UserPropertyAdapter<Damage>::template type<T>;
#endif

template <typename T>
struct DamagingImproved_ : T {  // example of improving build-in property - may be used as replacement of impl::Damaging_
    using property_data = PropertyData<impl::damaging_type_name, DamagingImproved_, T>;
    using improvement_of = Damaging_impl<T>;

    DamagingImproved_() noexcept = default;

    Damage dmg;
};
template <typename T>  // example of improving build-in property - may be used as replacement of Damaging
using DamagingImproved = std::conditional_t<Damagingable<T>, T, DamagingImproved_<T>>;

template <typename T>
using UserDamaging = UserProperty<Damage, T>;
template <typename T>
using UserProtecting = UserProperty<Protection, T>;
template <typename T>
using UserProtecting_2 = UserProperty<Protection, T>;

template <typename T>
struct UserProtectingImproved_ : T {  // example of improving user property
    using property_data = PropertyData<impl::user_type_name, UserProtectingImproved_, T>;
    using improvement_of = UserProtecting<T>;

    UserProtectingImproved_() noexcept = default;
};
template <typename T>
using UserProtectingImproved = std::conditional_t<getType_or_custom_accessable<T, Protection>, T, UserProtectingImproved_<T>>;

template <typename T>
struct UserProtectingImproved_2_ : T {  // example of improving use property
    using property_data = PropertyData<impl::user_type_name, UserProtectingImproved_2_, T>;
    using improvement_of = UserProtecting_2<T>;

    UserProtectingImproved_2_() noexcept = default;
};
template <typename T>
using UserProtectingImproved_2 = std::conditional_t<getType_or_custom_accessable<T, Protection>, T, UserProtectingImproved_2_<T>>;
