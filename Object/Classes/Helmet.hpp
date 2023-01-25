#pragma once
#include <string>
#include "../Types/AC.hpp"

class Helmet {
public:
	Helmet(const std::string& name, AC ac): name(name), ac(ac) {}
	
	std::string name;
	AC ac{};
};
