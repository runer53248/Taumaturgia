#pragma once
#include <string>
#include "../Types/Damage.hpp"

class Weapon {
public:
	Weapon(const std::string& name, Damage dmg): name(name), dmg(dmg) {}
	
	std::string name;
	Damage dmg{};
};
