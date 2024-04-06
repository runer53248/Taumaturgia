#pragma once
#include <iostream>
#include "Taumaturgia/Concepts/Types/Name.hpp"

auto& operator<<(std::ostream& out, const Name& name) {
    return out << std::string(name);
}
