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

    #include "Object/Concepts/Types/Name.hpp"
    #include "Object/Concepts/Types/Health.hpp"
    #include "Object/Concepts/Types/WearContainer.hpp"
    #include "Object/Concepts/Types/Damage.hpp"
    #include "Object/Concepts/Types/CureHealth.hpp"
    #include "Object/Concepts/Types/Protection.hpp"

    #include "Object/Concepts/Namingable.hpp"
    #include "Object/Strategies/Strategies.hpp" // will also include all properties concepts

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

    #ifndef NO_PREMADE_STRATEGIES
        template <typename T, typename... Args>
        struct WearStrategy_<impl::UserProperty_<WearContainer, T, Args...>> : WearStrategy_<T> {};  // forward eventualy implemented strategy
        template <typename T, typename... Args>
        struct AttackStrategy_<impl::UserProperty_<Damage, T, Args...>> : AttackStrategy_<T> {};  // forward eventualy implemented strategy
        template <typename T, typename... Args>
        struct DefendStrategy_<impl::UserProperty_<Protection, T, Args...>> : DefendStrategy_<T> {};  // forward eventualy implemented strategy
        template <typename T, typename... Args>
        struct HealStrategy_<impl::UserProperty_<CureHealth, T, Args...>> : HealStrategy_<T> {};  // forward eventualy implemented strategy
        template <typename T, typename... Args>
        struct RestoreStrategy_<impl::UserProperty_<EffectTypeContainer, T, Args...>> : RestoreStrategy_<T> {};  // forward eventualy implemented strategy
    #else
        template <typename T, typename... Args>
        struct UserStrategy_<WearContainer, impl::UserProperty_<WearContainer, T, Args...>> : UserStrategy_<WearContainer, T> {};  // forward eventualy implemented strategy
        template <typename T, typename... Args>
        struct UserStrategy_<Damage, impl::UserProperty_<Damage, T, Args...>> : UserStrategy_<Damage, T> {};  // forward eventualy implemented strategy
        template <typename T, typename... Args>
        struct UserStrategy_<Protection, impl::UserProperty_<Protection, T, Args...>> : UserStrategy_<Protection, T> {};  // forward eventualy implemented strategy
        template <typename T, typename... Args>
        struct UserStrategy_<CureHealth, impl::UserProperty_<CureHealth, T, Args...>> : UserStrategy_<CureHealth, T> {};  // forward eventualy implemented strategy
        template <typename T, typename... Args>
        struct UserStrategy_<EffectTypeContainer, impl::UserProperty_<EffectTypeContainer, T, Args...>> : UserStrategy_<EffectTypeContainer, T> {};  // forward eventualy implemented strategy
    #endif
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
