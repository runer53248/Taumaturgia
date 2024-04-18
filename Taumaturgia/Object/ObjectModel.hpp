#pragma once
#include "Enums/ActionStatus.hpp"
#include <map>

namespace action_impl {

template <typename T>
constexpr std::optional<AliveStatus> alive(const T& type) {
    if constexpr (is_alive_strategy<T>) {
        static constinit AliveStrategy<T> strategy_{};
        return strategy_(type);
    } else {
        return {};
    }
}

template <typename T>
constexpr auto get_impl(T& type, Properties param) {  // TODO: implement test for get
    using result_type = std::conditional_t<
        std::is_const_v<std::remove_reference_t<decltype(type)>>,
        optional_get_variant_const_type,
        optional_get_variant_type>;

    if constexpr (not Gettingable<T>) {
        return result_type{};
    } else {
        static constinit GetStrategy<T> getStrategy_{};
        switch (param) {
        case Properties::Protection:
            return getStrategy_.template operator()<Properties::Protection>(type);
        case Properties::Damage:
            return getStrategy_.template operator()<Properties::Damage>(type);
        case Properties::Health:
            return getStrategy_.template operator()<Properties::Health>(type);
        case Properties::CureHealth:
            return getStrategy_.template operator()<Properties::CureHealth>(type);
        case Properties::Restore:
            return getStrategy_.template operator()<Properties::Restore>(type);
        case Properties::Wear:
            return getStrategy_.template operator()<Properties::Wear>(type);
        default:
            return result_type{};
        };
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

template <Namingable T>
constexpr Object::ObjectModel<T>::ObjectModel(const T& type)
    : type_{type} {}

template <Namingable T>
constexpr std::string Object::ObjectModel<T>::name() const {
    return traits::accessName::get(type_);
}

template <Namingable T>
constexpr std::optional<AliveStatus> Object::ObjectModel<T>::alive() const {
    return action_impl::alive(type_);
}

template <Namingable T>
constexpr ActionStatus Object::ObjectModel<T>::action(Actions action, Object* owner, Object* target) const {
    static const auto commands_ = action_impl::createCommands(type_);

    if (not commands_.contains(action)) {
        return ActionStatus::None;
    }
    return commands_.at(action)->execute(owner, target);
}

template <Namingable T>
constexpr auto Object::ObjectModel<T>::get(Properties param) -> optional_get_variant_type {
    static_assert(not std::is_const_v<std::remove_reference_t<decltype((type_))>>);
    return action_impl::get_impl(type_, param);
}

template <Namingable T>
constexpr auto Object::ObjectModel<T>::get(Properties param) const -> optional_get_variant_const_type {
    static_assert(std::is_const_v<std::remove_reference_t<decltype((type_))>>);
    return action_impl::get_impl(type_, param);
}
