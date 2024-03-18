#pragma once
#include <string>
#include "Object/Concepts/Types/WearContainer.hpp"

struct Player {
    std::string name;  // string used as name
    WearContainer armorWear{10};
    EffectTypeContainer restoreEffects{EffectType::Infection};
};
