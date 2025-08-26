#pragma once
#include <string>
#include "Adapter.hpp"
#include "EmptyType.hpp"
#include "Usage/Types/WearContainer/WearContainer.hpp"

using PlayerBuild = add_properties_ordered<
    Type,
    Naming,
    Adapter<Wearing, struct Player_tag>::type,   // Wearing taged for custom default value
    Adapter<Restoring, struct Player_tag>::type  // Restoring taged for custom default value
    >;

template <>
struct UserDefaultValue<WearContainer, struct Player_tag> {
    static inline std::move_only_function<WearContainer()> value = [] { return WearContainer{10}; };
};

template <>
struct UserDefaultValue<EffectTypeContainer, struct Player_tag> {
    static constexpr auto value = [] { return EffectTypeContainer{EffectType::Infection}; };
};

struct PlayerClass {
    std::string name;  // string used as name
    WearContainer armorWear{10};
    EffectTypeContainer restoreEffects{EffectType::Infection};
};

#ifdef WITH_ADD_PROPERTIES
#define USES_ADD_PROPERTIES
using Player = PlayerBuild;
#else
using Player = PlayerClass;
#endif
