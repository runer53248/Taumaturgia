#pragma once
#include <string>
#include "Adapter.hpp"
#include "EmptyType.hpp"

using PlayerBuild = add_properties_ordered<
    Type,
    Naming,
    Adapter<Wearing, struct Player_tag>::type,   // taged for custom default value
    Adapter<Restoring, struct Player_tag>::type  // taged for custom default value
    >;

template <>
struct UserDefaultValue<property_t<Wearing>, struct Player_tag> {
    static inline std::move_only_function<property_t<Wearing>()> value = [] { return property_t<Wearing>{10}; };
};

template <>
struct UserDefaultValue<property_t<Restoring>, struct Player_tag> {
    static constexpr auto value = [] { return property_t<Restoring>{EffectType::Infection}; };
};

struct PlayerClass {
    template <size_t S = 0, typename Self>
        requires(S < 3)
    decltype(auto) getType(this Self&& self) {
        if constexpr (S == 0) {
            return (self.name);
        } else if constexpr (S == 1) {
            return (self.armorWear);
        } else {
            return (self.restoreEffects);
        }
    }
    template <size_t S = 0, typename Self>
    decltype(auto) getType(this Self&& self) = delete;

    template <typename T, size_t S = 0, typename Self>
        requires(std::same_as<T, property_t<Naming>> and S == 0)
    decltype(auto) getType(this Self&& self) {
        return (self.name);
    }
    template <typename T, size_t S = 0, typename Self>
        requires(std::same_as<T, property_t<Wearing>> and S == 0)
    decltype(auto) getType(this Self&& self) {
        return (self.armorWear.value);
    }
    template <typename T, size_t S = 0, typename Self>
        requires(std::same_as<T, Data<property_t<Wearing>, struct Player_tag>> and S == 0)
    decltype(auto) getType(this Self&& self) {
        return (self.armorWear);
    }
    template <typename T, size_t S = 0, typename Self>
        requires(std::same_as<T, property_t<Restoring>> and S == 0)
    decltype(auto) getType(this Self&& self) {
        return (self.restoreEffects);
    }
    template <typename T, size_t S, typename Self>
    decltype(auto) getType(this Self&& self) = delete;

    std::string name;  // string used as name
    Data<property_t<Wearing>, struct Player_tag> armorWear{10};
    property_t<Restoring> restoreEffects{EffectType::Infection};
};

#ifdef WITH_ADD_PROPERTIES
#define USES_ADD_PROPERTIES
using Player = PlayerBuild;
#else
using Player = PlayerClass;
#endif
