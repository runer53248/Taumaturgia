#pragma once
#include <string>
#include "Taumaturgia/Types/WearContainer.hpp"

struct Player {
    std::string name;  // string used as name
    WearContainer armorWear{10};
    EffectTypeContainer restoreEffects{EffectType::Infection};
};
