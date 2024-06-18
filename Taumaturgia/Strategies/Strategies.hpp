#pragma once
#include "Taumaturgia/Properties/Properties.hpp"

#include "GetStrategy.hpp"  //

#ifdef NO_PREMADE_STRATEGIES
#include "Taumaturgia/User/UserStrategies.hpp"
#else
#include "Premade/PremadeStrategies.hpp"
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
