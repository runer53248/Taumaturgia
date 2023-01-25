#pragma once
#include <string>
#include "../Types/Damage.hpp"

struct Weapon {
	std::string name;
	Damage dmg{};
};
