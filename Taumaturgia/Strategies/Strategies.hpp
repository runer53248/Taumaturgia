#pragma once
#include "Taumaturgia/Properties/Properties.hpp"

#ifndef NO_PREMADE_STRATEGIES

    #include "GetStrategy.hpp"
    #include "Premade/AliveStrategy.hpp"
    #include "Premade/AttackStrategy.hpp"
    #include "Premade/DefendStrategy.hpp"
    #include "Premade/HealStrategy.hpp"
    #include "Premade/RestoreStrategy.hpp"
    #include "Premade/WearStrategy.hpp"

#else

    class Object;
    enum class ActionStatus;
    enum class AliveStatus : signed char;

    #include "GetStrategy.hpp"
    #include "UserStrategy.hpp"
    
    template <typename T>
    using AliveStrategy = UserStrategy<Health, T, Livingable<T>, std::optional<AliveStatus>>;
    template <typename T>
    concept is_alive_strategy = Strategable<AliveStrategy, T, std::optional<AliveStatus>>;

    template <typename T>
    using AttackStrategy = UserStrategy<Damage, T, Damagingable<T>, ActionStatus, Object*, Object*>;
    template <typename T>
    concept is_attack_strategy = Strategable<AttackStrategy, T, ActionStatus, Object*, Object*>;

    template <typename T>
    using DefendStrategy = UserStrategy<Protection, T, Protectingable<T>, ActionStatus, Object*, Object*>;
    template <typename T>
    concept is_defend_strategy = Strategable<DefendStrategy, T, ActionStatus, Object*, Object*>;

    template <typename T>
    using WearStrategy = UserStrategy<WearContainer, T, Wearingable<T>, ActionStatus, Object*, Object*>;
    template <typename T>
    concept is_wear_strategy = Strategable<WearStrategy, T, ActionStatus, Object*, Object*>;

    template <typename T>
    using RestoreStrategy = UserStrategy<EffectTypeContainer, T, Restoringable<T>, ActionStatus, Object*, Object*>;
    template <typename T>
    concept is_restore_strategy = Strategable<RestoreStrategy, T, ActionStatus, Object*, Object*>;

    template <typename T>
    using HealStrategy = UserStrategy<CureHealth, T, Healingable<T>, ActionStatus, Object*, Object*>;
    template <typename T>
    concept is_heal_strategy = Strategable<HealStrategy, T, ActionStatus, Object*, Object*>;

#endif

#ifndef NO_PREMADE_STRATEGIES

    template <typename T>
    struct WearStrategy_<Wearing_impl<T>> : public WearStrategy_<T> {};  // forward eventualy implemented strategy
    template <typename T>
    struct AttackStrategy_<Damaging_impl<T>> : public AttackStrategy_<T> {};  // forward eventualy implemented strategy
    template <typename T>
    struct DefendStrategy_<Protecting_impl<T>> : public DefendStrategy_<T> {};  // forward eventualy implemented strategy
    template <typename T>
    struct HealStrategy_<Healing_impl<T>> : public HealStrategy_<T> {};  // forward eventualy implemented strategy
    template <typename T>
    struct RestoreStrategy_<Restoring_impl<T>> : public RestoreStrategy_<T> {};  // forward eventualy implemented strategy

#else

    template <typename T>
    struct UserStrategy_<Health, Healing_impl<T>, std::optional<AliveStatus>> : public UserStrategy_<Health, T, std::optional<AliveStatus>> {};  // forward eventualy implemented strategy
    template <typename T>
    struct UserStrategy_<WearContainer, Wearing_impl<T>, ActionStatus> : public UserStrategy_<WearContainer, T, ActionStatus> {};  // forward eventualy implemented strategy
    template <typename T>
    struct UserStrategy_<Damage, Damaging_impl<T>, ActionStatus> : public UserStrategy_<Damage, T, ActionStatus> {};  // forward eventualy implemented strategy
    template <typename T>
    struct UserStrategy_<Protection, Protecting_impl<T>, ActionStatus> : public UserStrategy_<Protection, T, ActionStatus> {};  // forward eventualy implemented strategy
    template <typename T>
    struct UserStrategy_<CureHealth, Healing_impl<T>, ActionStatus> : public UserStrategy_<CureHealth, T, ActionStatus> {};  // forward eventualy implemented strategy
    template <typename T>
    struct UserStrategy_<EffectTypeContainer, Restoring_impl<T>, ActionStatus> : public UserStrategy_<EffectTypeContainer, T, ActionStatus> {};  // forward eventualy implemented strategy
    
#endif

template <Namingable T>
auto propertiesExistanceMap() {
    return std::unordered_map<Properties, const bool>{
        {Properties::Health, is_alive_strategy<T>},
        {Properties::CureHealth, is_heal_strategy<T>},
        {Properties::Protection, is_defend_strategy<T>},
        {Properties::Damage, is_attack_strategy<T>},
        {Properties::Restore, is_restore_strategy<T>},
        {Properties::Wear, is_wear_strategy<T>},
        {Properties::Get, is_get_strategy<T>}};
}
