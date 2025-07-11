#pragma once
#include "Usage/Properties.hpp"

template <typename T>
struct DamagingImproved_ : public T {  // example of improving build-in property - may be used as replacement of impl::Damaging_
    using property_data = PropertyData<DamagingImproved_, T>;
    // using hold_type = Damaging_impl<T>::hold_type;
    using improvement_of = Damaging_impl<T>;
    using hold_type = void;

    DamagingImproved_() noexcept = default;

    Damage dmg;
};
template <typename T>  // example of improving build-in property - may be used as replacement of Damaging
using DamagingImproved = std::conditional_t<Damagingable<T>,
                                            T,
                                            DamagingImproved_<T>>;

template <typename T>
struct UserProtectingImproved_ : public T {  // example of improving user property
    using property_data = PropertyData<UserProtectingImproved_, T>;
    using improvement_of = Protecting_impl<T>;
    using hold_type = void;

    UserProtectingImproved_() noexcept = default;
};
template <typename T>
using UserProtectingImproved = std::conditional_t<trait_accessable<T, Protection>,
                                                  T,
                                                  UserProtectingImproved_<T>>;

template <typename T>
struct UserProtectingImproved_2_ : public T {  // example of improving use property
    using property_data = PropertyData<UserProtectingImproved_2_, T>;
    using improvement_of = Protecting_impl<T>;
    using hold_type = void;

    UserProtectingImproved_2_() noexcept = default;
};
template <typename T>
using UserProtectingImproved_2 = std::conditional_t<trait_accessable<T, Protection>,
                                                    T,
                                                    UserProtectingImproved_2_<T>>;
