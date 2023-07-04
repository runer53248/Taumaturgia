#pragma once
#include <string>
#include "Object/Concepts/Types/ProtectionContainer.hpp"

struct Player {
    std::string name;  // string used as name
    ProtectionContainer armorWear{10};
};
