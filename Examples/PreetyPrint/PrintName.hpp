#pragma once
#include <iostream>
#include "../../Object/Concepts/Types/Name.hpp"

constexpr auto& operator<<(std::ostream& out, const Name& name) {
    return out << std::string(name);
}
