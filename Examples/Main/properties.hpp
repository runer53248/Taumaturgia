#pragma once

#ifndef USER_PROPERTIES
    // use prepared properties
    #include "Object/Properties/Properties.hpp"

#else
    // simulate prepared properties with UserProperty class
    #include "Object/Properties/UserProperty.hpp"

    template <typename TYPE>
    using Living = UserPropertyConceptAdapter<Health, Livingable<TYPE>>::template type<TYPE>;
    template <typename TYPE>
    using Wearing = UserPropertyConceptAdapter<ProtectionContainer, Wearingable<TYPE>>::template type<TYPE>;
    template <typename TYPE>
    using Damaging = UserPropertyConceptAdapter<Damage, Damagingable<TYPE>>::template type<TYPE>;
    template <typename TYPE>
    using Protecting = UserPropertyConceptAdapter<Protection, Protectingable<TYPE>>::template type<TYPE>;
    template <typename TYPE>
    using Healing = UserPropertyConceptAdapter<CureHealth, Healingable<TYPE>>::template type<TYPE>;
    template <typename TYPE>
    using Restoring = UserPropertyConceptAdapter<EffectTypeContainer, Restoringable<TYPE>>::template type<TYPE>;
    template <typename TYPE>
    using Naming = UserPropertyConceptAdapter<Name, Namingable<TYPE>>::template type<TYPE>;

    #include "Object/Properties/Helpers/taged_list.hpp"

    using order_list = taged_list<
        Living,
        Wearing,
        Damaging,
        Protecting,
        Healing,
        Restoring,
        Naming  // Naming should be last property to add (used closest to type)
        >;      // properties list in order

    #include "Object/Properties/Helpers/Property.hpp"
#endif

struct Living_type {
    Name name;
    Health hp;
};

static_assert(std::is_same_v<
                Damaging<Living_type>,
                add_properties<Living_type, Naming, Living, Damaging> >);
