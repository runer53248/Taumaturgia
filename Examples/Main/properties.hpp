#pragma once

#ifndef USER_PROPERTIES
    // use prepared properties
    #include "Object/Properties/Properties.hpp"

#else
    // simulate prepared properties with UserProperty class
    #include "Object/Properties/UserProperty.hpp"

    template <typename TYPE, bool CONCEPT>
    struct UserPropertyAdapter {
        template <typename T>
        using type = std::conditional_t<CONCEPT, T, UserProperty<TYPE, T>>;
    };

    template <typename TYPE>
    using Living = UserPropertyAdapter<Health, Livingable<TYPE>>::template type<TYPE>;
    template <typename TYPE>
    using Wearing = UserPropertyAdapter<ProtectionContainer, Wearingable<TYPE>>::template type<TYPE>;
    template <typename TYPE>
    using Damaging = UserPropertyAdapter<Damage, Damagingable<TYPE>>::template type<TYPE>;
    template <typename TYPE>
    using Protecting = UserPropertyAdapter<Protection, Protectingable<TYPE>>::template type<TYPE>;
    template <typename TYPE>
    using Healing = UserPropertyAdapter<CureHealth, Healingable<TYPE>>::template type<TYPE>;
    template <typename TYPE>
    using Restoring = UserPropertyAdapter<EffectTypeContainer, Restoringable<TYPE>>::template type<TYPE>;
    template <typename TYPE>
    using Naming = UserPropertyAdapter<Name, Namingable<TYPE>>::template type<TYPE>;

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

    struct Living_type {
        Name name;
        Health hp;
    };

    static_assert(std::is_same_v<Damaging<Living_type>, add_properties<Living_type, Naming, Living, Damaging>>);

#endif
