#pragma once
#include "Object/Concepts/Types/Damage.hpp"
#include "Object/Concepts/Types/Name.hpp"

struct Weapon {
    Name name;
    Damage dmg{};
};
