#pragma once

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

#endif
