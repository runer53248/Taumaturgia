#pragma once
#include <map>
#include <optional>
#include "Command.hpp"
#include "Usage/Enums/Actions.hpp"

namespace action_impl {

template <typename T>
constexpr std::optional<AliveStatus> alive(const T& type) {
    if constexpr (is_alive_strategy<T>) {
        return AliveStrategy<T>::operator()(type);
    } else {
        return {};
    }
}

template <typename T>
constexpr auto get_impl(T& type, Properties param) -> to_optional_get_variant<T> {  // TODO: implement test for get
    if constexpr (not Gettingable<T>) {
        return {};
    } else {
        using strategy = GetStrategy<std::remove_const_t<T>>;

        switch (param) {
        case Properties::Protection:
            return strategy::template operator()<Properties::Protection>(type);
        case Properties::Damage:
            return strategy::template operator()<Properties::Damage>(type);
        case Properties::Health:
            return strategy::template operator()<Properties::Health>(type);
        case Properties::CureHealth:
            return strategy::template operator()<Properties::CureHealth>(type);
        case Properties::Restore:
            return strategy::template operator()<Properties::Restore>(type);
        case Properties::Wear:
            return strategy::template operator()<Properties::Wear>(type);
        case Properties::Name:
            return strategy::template operator()<Properties::Name>(type);
        default:
            return {};
        };
    }
}

template <typename T, Properties P>
constexpr auto get_impl(T& type, sProperties<P>) {  // TODO: implement test for get
    if constexpr (not is_properties_accessable<P, T>) {
        return;
    } else {
        return GetStrategy<std::remove_const_t<T>>::template operator()<P>(type);
    }
}

template <typename T>
auto createCommands(T& type) {
    return std::unordered_map<Actions, std::shared_ptr<CommandConcept>>{
        {Actions::Attack, std::make_shared<CommandModel<T, AttackStrategy>>(type)},
        {Actions::Defend, std::make_shared<CommandModel<T, DefendStrategy>>(type)},
        {Actions::Heal, std::make_shared<CommandModel<T, HealStrategy>>(type)},
        {Actions::Restore, std::make_shared<CommandModel<T, RestoreStrategy>>(type)},
        {Actions::Wear, std::make_shared<CommandModel<T, WearStrategy>>(type)}};
}

}  // namespace action_impl
