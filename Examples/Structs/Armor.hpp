#pragma once
#include "EmptyType.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "Usage/Types/Protection/Protection.hpp"

using ArmorBuild = add_properties_ordered<
    Type,
    Naming,
    Protecting>;

// struct Armor_Class {
//     Name name;
//     Protection protection{};
// };

class Armor_Class {
public:
    Armor_Class(std::string name, Protection protection)
        : name{name}, protection{protection} {}

    auto& getProtection() noexcept {
        return protection;
    }

    const auto& getProtection() const noexcept {
        return protection;
    }

    Name name;

private:
    Protection protection;
};

#ifdef WITH_ADD_PROPERTIES
using Armor = ArmorBuild;
#else
using Armor = Armor_Class;
#endif
