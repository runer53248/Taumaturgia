#pragma once
#include <string>
#include "../Types/AC.hpp"

class Armor {
public:
	Armor(const std::string& name, AC ac): name(name), ac(ac) {}
	
	std::string name;
	AC ac{};
};
