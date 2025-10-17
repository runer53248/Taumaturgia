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
    std::string name;  // string used as name
    property_t<Wearing> armorWear{10};
    property_t<Restoring> restoreEffects{EffectType::Infection};
};

#ifdef WITH_ADD_PROPERTIES
#define USES_ADD_PROPERTIES
using Player = PlayerBuild;
#else
using Player = PlayerClass;
#endif
