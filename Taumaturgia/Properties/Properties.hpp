#pragma once

#ifndef NO_PREMADE_PROPERTIES
    #include "Premade/Damaging.hpp"
    #include "Premade/Healing.hpp"
    #include "Premade/Living.hpp"
    #include "Premade/Naming.hpp"
    #include "Premade/Protecting.hpp"
    #include "Premade/Restoring.hpp"
    #include "Premade/Wearing.hpp"

    template <typename T>
    using Living_impl = impl::Living_<T>;
    template <typename T> 
    using Wearing_impl = impl::Wearing_<T>;
    template <typename T>
    using Damaging_impl = impl::Damaging_<T>;
    template <typename T>
    using Protecting_impl = impl::Protecting_<T>;
    template <typename T>
    using Healing_impl = impl::Healing_<T>;
    template <typename T>
    using Restoring_impl = impl::Restoring_<T>;
#else
    #include "UserProperty.hpp"

    #include "Taumaturgia/Traits/NameTraits.hpp"
    #include "Taumaturgia/Traits/HealthTraits.hpp"
    #include "Taumaturgia/Traits/ArmorWearTraits.hpp"
    #include "Taumaturgia/Traits/DamageTraits.hpp"
    #include "Taumaturgia/Traits/CureHealthTraits.hpp"
    #include "Taumaturgia/Traits/ProtectionTraits.hpp"
    #include "Taumaturgia/Traits/RestoreEffectsTraits.hpp"

    #include "Taumaturgia/Types/Name.hpp"
    #include "Taumaturgia/Types/Health.hpp"
    #include "Taumaturgia/Types/WearContainer.hpp"
    #include "Taumaturgia/Types/Damage.hpp"
    #include "Taumaturgia/Types/CureHealth.hpp"
    #include "Taumaturgia/Types/Protection.hpp"

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

    template <typename T>
    using Living_impl = impl::UserProperty_<Health, T>;
    template <typename T> 
    using Wearing_impl = impl::UserProperty_<WearContainer, T>;
    template <typename T>
    using Damaging_impl = impl::UserProperty_<Damage, T>;
    template <typename T>
    using Protecting_impl = impl::UserProperty_<Protection, T>;
    template <typename T>
    using Healing_impl = impl::UserProperty_<CureHealth, T>;
    template <typename T>
    using Restoring_impl = impl::UserProperty_<EffectTypeContainer, T>;
#endif

#include "Helpers/taged_list.hpp"

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
