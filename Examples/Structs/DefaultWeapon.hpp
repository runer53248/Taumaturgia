#pragma once
#include <string>
#include "Object/Concepts/Types/Damage.hpp"

struct DefaultWeapon {
    std::string name;  // string used as name
    Damage dmg{};
};
