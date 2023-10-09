#pragma once
#include <iostream>
#include "../../Object/Concepts/Types/Name.hpp"

std::ostream& operator<<(std::ostream& out, const Name& name) {
    out << name.operator std::string();
    return out;
}
