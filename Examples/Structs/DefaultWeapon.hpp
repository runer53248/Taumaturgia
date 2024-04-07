#pragma once
#include <string>
#include "Taumaturgia/Types/Damage.hpp"

struct DefaultWeapon {
    std::string name;  // string used as name
    Damage dmg{};
};
