#pragma once
#include "Taumaturgia/Enums/ActionStatus.hpp"

namespace action_impl {

namespace details {

template <Actions Action, typename T, typename... Args>
static constexpr ActionStatus action([[maybe_unused]] const T& type, [[maybe_unused]] Args&&... args) {
    return ActionStatus::None;
}

template <Actions Action, is_attack_strategy T, typename... Args>
    requires(Action == Actions::Attack)
static constexpr ActionStatus action(const T& type, Args&&... args) {
    static constinit AttackStrategy<T> strategy_{};
    return strategy_(type, std::forward<Args>(args)...);
}

template <Actions Action, is_defend_strategy T, typename... Args>
    requires(Action == Actions::Defend)
static constexpr ActionStatus action(const T& type, Args&&... args) {
    static constinit DefendStrategy<T> strategy_{};
    return strategy_(type, std::forward<Args>(args)...);
}

template <Actions Action, is_wear_strategy T, typename... Args>
    requires(Action == Actions::Wear)
static constexpr ActionStatus action(const T& type, Args&&... args) {
    static constinit WearStrategy<T> strategy_{};
    return strategy_(type, std::forward<Args>(args)...);
}

template <Actions Action, is_heal_strategy T, typename... Args>
    requires(Action == Actions::Heal)
static constexpr ActionStatus action(const T& type, Args&&... args) {
    static constinit HealStrategy<T> strategy_{};
    return strategy_(type, std::forward<Args>(args)...);
}

template <Actions Action, is_restore_strategy T, typename... Args>
    requires(Action == Actions::Restore)
static constexpr ActionStatus action(const T& type, Args&&... args) {
    static constinit RestoreStrategy<T> strategy_{};
    return strategy_(type, std::forward<Args>(args)...);
}

}  // namespace details

template <typename T>
constexpr std::optional<AliveStatus> alive([[maybe_unused]] const T& type) {
    return {};
}

template <is_alive_strategy T>
constexpr std::optional<AliveStatus> alive(const T& type) {
    static constinit AliveStrategy<T> strategy_{};
    return strategy_(type);
}

template <typename... Args>
constexpr ActionStatus action(Actions action, Namingable auto const& type, Args&&... args) {
    switch (action) {
    case Actions::Attack:
        return details::action<Actions::Attack>(type, std::forward<Args>(args)...);
    case Actions::Defend:
        return details::action<Actions::Defend>(type, std::forward<Args>(args)...);
    case Actions::Heal:
        return details::action<Actions::Heal>(type, std::forward<Args>(args)...);
    case Actions::Restore:
        return details::action<Actions::Restore>(type, std::forward<Args>(args)...);
    case Actions::Wear:
        return details::action<Actions::Wear>(type, std::forward<Args>(args)...);
    default:
        return ActionStatus::None;
    }
}

template <typename T>
constexpr auto get_impl(T& type, Properties param) {  // TODO: implement test for get
    using result_type = std::conditional_t<
        std::is_const_v<std::remove_reference_t<decltype(type)>>,
        get_optional_variant_const_type,
        get_optional_variant_type>;

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

}  // namespace action_impl
