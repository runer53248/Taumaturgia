#pragma once
#include <iostream>
#include "Usage/Types/Name/Name.hpp"

auto& operator<<(std::ostream& out, const Name& name) {
    return out << std::string(name);
}
