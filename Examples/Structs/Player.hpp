#pragma once
#include <string>
#include "EmptyType.hpp"
#include "Usage/Types/WearContainer/WearContainer.hpp"
using PlayerBuild = add_properties_ordered<
    Type,
    Naming,
    Wearing,
    Restoring>;

struct PlayerClass {
    std::string name;                                           // string used as name
    WearContainer armorWear{10};                                // TODO: default values
    EffectTypeContainer restoreEffects{EffectType::Infection};  // TODO: default values
};

#ifdef WITH_ADD_PROPERTIES
using Player = PlayerBuild;
#else
using Player = PlayerClass;
#endif
