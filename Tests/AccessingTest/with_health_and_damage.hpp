#pragma once
#include "Usage/With.hpp"

// MARK: with_health_and_damage

struct with_health_and_damage {
private:
    Health other_hp{};
    Damage other_dmg{};

public:
    with_health_and_damage() = default;
    with_health_and_damage(const Health& other_hp) : other_hp{other_hp} {}

    template <size_t S, typename Self>
    constexpr decltype(auto) getType(this Self& self) noexcept {
        if constexpr (S == 0) {
            return (self.other_hp);
        } else {
            return (self.other_dmg);
        }
    }
    template <size_t S, typename Self>
        requires(S > 1)
    constexpr decltype(auto) getType(this Self& self) noexcept = delete;

    template <typename Type, isTag TAGS = no_tag, typename Self>
        requires((std::same_as<Type, Health> or std::same_as<Type, Damage>) and TAGS::size == 0)
    constexpr decltype(auto) getTypeTaged(this Self& self) noexcept {
        if constexpr (std::same_as<Type, Health>)
            return (self.other_hp);
        if constexpr (std::same_as<Type, Damage>)
            return (self.other_dmg);
    }
    template <typename Type, isTag TAGS, typename Self>
    constexpr decltype(auto) getTypeTaged(this Self& self) noexcept = delete;
};
