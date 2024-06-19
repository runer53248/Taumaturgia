#pragma once
#include "Usage/Properties.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

#ifdef NO_PREMADE_PROPERTIES
namespace impl {
constinit const char damaging_type_name[] = "Damaging";
}
#endif

template <typename T>
struct DamagingImproved_ : public T {  // example of improving build-in property - may be used as replacement of impl::Damaging_
    using property_data = PropertyData<impl::damaging_type_name, DamagingImproved_, T>;
    using improvement_of = Damaging_impl<T>;

    DamagingImproved_() noexcept = default;

    Damage dmg;
};
template <typename T>  // example of improving build-in property - may be used as replacement of Damaging
using DamagingImproved = std::conditional_t<Damagingable<T>,
                                            T,
                                            DamagingImproved_<T>>;

template <typename T>
struct UserProtectingImproved_ : public T {  // example of improving user property
    using property_data = PropertyData<impl::user_type_name, UserProtectingImproved_, T>;
    using improvement_of = Protecting_impl<T>;

    UserProtectingImproved_() noexcept = default;
};
template <typename T>
using UserProtectingImproved = std::conditional_t<accessType_trait_able<T, Protection>,
                                                  T,
                                                  UserProtectingImproved_<T>>;

template <typename T>
struct UserProtectingImproved_2_ : public T {  // example of improving use property
    using property_data = PropertyData<impl::user_type_name, UserProtectingImproved_2_, T>;
    using improvement_of = Protecting_impl<T>;

    UserProtectingImproved_2_() noexcept = default;
};
template <typename T>
using UserProtectingImproved_2 = std::conditional_t<accessType_trait_able<T, Protection>,
                                                    T,
                                                    UserProtectingImproved_2_<T>>;
