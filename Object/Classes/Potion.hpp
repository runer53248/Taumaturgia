#pragma once
#include <string>

class Potion {
public:
	Potion(const std::string& name): name(name) {}
	
	std::string name;
};
