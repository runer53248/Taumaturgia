#pragma once
#include <string>
#include "Usage/Types/WearContainer/WearContainer.hpp"

#ifdef WITH_ADD_PROPERTIES
#include "EmptyType.hpp"
using Player = add_properties<Type, Naming, Wearing, Restoring>;
#else

struct Player {
    std::string name;                                           // string used as name
    WearContainer armorWear{10};                                // TODO: default values
    EffectTypeContainer restoreEffects{EffectType::Infection};  // TODO: default values
};

#endif
