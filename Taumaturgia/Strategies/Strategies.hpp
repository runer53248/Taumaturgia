#pragma once
#include "Taumaturgia/Properties/Properties.hpp"

#ifndef NO_PREMADE_STRATEGIES

    #include "AliveStrategy.hpp"
    #include "GetStrategy.hpp"
    #include "Premade/AttackStrategy.hpp"
    #include "Premade/DefendStrategy.hpp"
    #include "Premade/HealStrategy.hpp"
    #include "Premade/RestoreStrategy.hpp"
    #include "Premade/WearStrategy.hpp"

#else

    #include "AliveStrategy.hpp"
    #include "GetStrategy.hpp"
    #include "UserStrategy.hpp"

    template <typename T>
    using AttackStrategy = UserStrategy<Damage, T, Damagingable<T>>;
    template <typename T>
    concept is_attack_strategy = Strategable<AttackStrategy, T, ActionStatus, Object*, Object*>;
    template <>
    struct UserStrategy_<Damage, Default> {
        ActionStatus operator()(Damagingable auto& obj, Object* owner, Object* target) const;
    };

    template <typename T>
    using DefendStrategy = UserStrategy<Protection, T, Protectingable<T>>;
    template <typename T>
    concept is_defend_strategy = Strategable<DefendStrategy, T, ActionStatus, Object*, Object*>;
    template <>
    struct UserStrategy_<Protection, Default> {
        ActionStatus operator()(Protectingable auto& obj, Object* owner, Object* target) const;
    };

    template <typename T>
    using WearStrategy = UserStrategy<WearContainer, T, Wearingable<T>>;
    template <typename T>
    concept is_wear_strategy = Strategable<WearStrategy, T, ActionStatus, Object*, Object*>;
    template <>
    struct UserStrategy_<WearContainer, Default> {
        ActionStatus operator()(Wearingable auto& obj, Object* owner, Object* target) const;
    };

    template <typename T>
    using RestoreStrategy = UserStrategy<EffectTypeContainer, T, Restoringable<T>>;
    template <typename T>
    concept is_restore_strategy = Strategable<RestoreStrategy, T, ActionStatus, Object*, Object*>;
    template <>
    struct UserStrategy_<EffectTypeContainer, Default> {
        ActionStatus operator()(Restoringable auto& obj, Object* owner, Object* target) const;
    };

    template <typename T>
    using HealStrategy = UserStrategy<CureHealth, T, Healingable<T>>;
    template <typename T>
    concept is_heal_strategy = Strategable<HealStrategy, T, ActionStatus, Object*, Object*>;
    template <>
    struct UserStrategy_<CureHealth, Default> {
        ActionStatus operator()(Healingable auto& obj, Object* owner, Object* target) const;
    };

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
    struct UserStrategy_<WearContainer, Wearing_impl<T>> : public UserStrategy_<WearContainer, T> {};  // forward eventualy implemented strategy
    template <typename T>
    struct UserStrategy_<Damage, Damaging_impl<T>> : public UserStrategy_<Damage, T> {};  // forward eventualy implemented strategy
    template <typename T>
    struct UserStrategy_<Protection, Protecting_impl<T>> : public UserStrategy_<Protection, T> {};  // forward eventualy implemented strategy
    template <typename T>
    struct UserStrategy_<CureHealth, Healing_impl<T>> : public UserStrategy_<CureHealth, T> {};  // forward eventualy implemented strategy
    template <typename T>
    struct UserStrategy_<EffectTypeContainer, Restoring_impl<T>> : public UserStrategy_<EffectTypeContainer, T> {};  // forward eventualy implemented strategy
    
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
