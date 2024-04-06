#pragma once

#ifndef NO_PREMADE_PROPERTIES
    #include "Premade/Damaging.hpp"
    #include "Premade/Healing.hpp"
    #include "Premade/Living.hpp"
    #include "Premade/Naming.hpp"
    #include "Premade/Protecting.hpp"
    #include "Premade/Restoring.hpp"
    #include "Premade/Wearing.hpp"
#else
    #include "UserProperty.hpp"

    template <typename TYPE>
    using Living = UserPropertyConceptAdapter<Health, Livingable<TYPE>>::template type<TYPE>;
    template <typename TYPE>
    using Wearing = UserPropertyConceptAdapter<WearContainer, Wearingable<TYPE>>::template type<TYPE>;
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

    #include "Helpers/taged_list.hpp"
#endif

using order_list = taged_list<
    Living,
    Wearing,
    Damaging,
    Protecting,
    Healing,
    Restoring,
    Naming  // should be last property to add (used closest to type)
    >;

#include "Helpers/Property.hpp"
