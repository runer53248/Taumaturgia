#pragma once
#include "Object/Concepts/Types/Name.hpp"
#include "Object/Concepts/Types/Protection.hpp"

struct Helmet {
    Name name;
    Protection protection{};
};
