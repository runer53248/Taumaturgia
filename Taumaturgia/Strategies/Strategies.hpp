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
    #include "AliveStrategy.hpp"
    #include "GetStrategy.hpp"

    #include "UserStrategy.hpp"

    template <typename T>
    using AttackStrategy = UserStrategyWithConcept<Damage, T, Damagingable<T>>;
    template <typename T>
    concept is_attack_strategy = UserStrategy_able<AttackStrategy, T>;
    template <>
    struct UserStrategy_<Damage, Default> {
        ActionStatus operator()(Damagingable auto& obj, Object* owner, Object* target) const;
    };

    template <typename T>
    using DefendStrategy = UserStrategyWithConcept<Protection, T, Protectingable<T>>;
    template <typename T>
    concept is_defend_strategy = UserStrategy_able<DefendStrategy, T>;
    template <>
    struct UserStrategy_<Protection, Default> {
        ActionStatus operator()(Protectingable auto& obj, Object* owner, Object* target) const;
    };

    template <typename T>
    using WearStrategy = UserStrategyWithConcept<WearContainer, T, Wearingable<T>>;
    template <typename T>
    concept is_wear_strategy = UserStrategy_able<WearStrategy, T>;
    template <>
    struct UserStrategy_<WearContainer, Default> {
        ActionStatus operator()(Wearingable auto& obj, Object* owner, Object* target) const;
    };

    template <typename T>
    using RestoreStrategy = UserStrategyWithConcept<EffectTypeContainer, T, Restoringable<T>>;
    template <typename T>
    concept is_restore_strategy = UserStrategy_able<RestoreStrategy, T>;
    template <>
    struct UserStrategy_<EffectTypeContainer, Default> {
        ActionStatus operator()(Restoringable auto& obj, Object* owner, Object* target) const;
    };

    template <typename T>
    using HealStrategy = UserStrategyWithConcept<CureHealth, T, Healingable<T>>;
    template <typename T>
    concept is_heal_strategy = UserStrategy_able<HealStrategy, T>;
    template <>
    struct UserStrategy_<CureHealth, Default> {
        ActionStatus operator()(Healingable auto& obj, Object* owner, Object* target) const;
    };

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
