#pragma once
#include "Usage/Properties.hpp"

#ifdef NO_PREMADE_STRATEGIES
#include "Usage/User/UserStrategies.hpp"
#else
#include "Usage/Premade/PremadeStrategies.hpp"
#endif

#include "Taumaturgia/Strategies/GetStrategy.hpp"  //

template <typename T>
concept is_alive_strategy = Strategable<AliveStrategy, T, std::optional<AliveStatus>>;
template <typename T>
concept is_attack_strategy = Strategable<AttackStrategy, T, ActionStatus, Object*, Object*>;
template <typename T>
concept is_defend_strategy = Strategable<DefendStrategy, T, ActionStatus, Object*, Object*>;
template <typename T>
concept is_wear_strategy = Strategable<WearStrategy, T, ActionStatus, Object*, Object*>;
template <typename T>
concept is_restore_strategy = Strategable<RestoreStrategy, T, ActionStatus, Object*, Object*>;
template <typename T>
concept is_heal_strategy = Strategable<HealStrategy, T, ActionStatus, Object*, Object*>;

template <Namingable T>
auto propertiesExistanceMap() {
    return std::unordered_map<Properties, const bool>{
        {Properties::Health, is_alive_strategy<T>},
        {Properties::CureHealth, is_heal_strategy<T>},
        {Properties::Protection, is_defend_strategy<T>},
        {Properties::Damage, is_attack_strategy<T>},
        {Properties::Restore, is_restore_strategy<T>},
        {Properties::Wear, is_wear_strategy<T>},
        {Properties::Get, Gettingable<T>}};
}

template <Namingable T>
auto propertiesCustomizationMap() {
    return std::unordered_map<Properties, const bool>{
        {Properties::Health, is_custom_alive_strategy<T>},
        {Properties::CureHealth, is_custom_heal_strategy<T>},
        {Properties::Protection, is_custom_defend_strategy<T>},
        {Properties::Damage, is_custom_attack_strategy<T>},
        {Properties::Restore, is_custom_restore_strategy<T>},
        {Properties::Wear, is_custom_wear_strategy<T>},
        {Properties::Get, is_custom_get_strategy<T>}
    };
}
