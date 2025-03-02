#pragma once
#include "Usage/Types/Name/Name.hpp"
#include "Usage/Types/Protection/Protection.hpp"

#ifdef WITH_ADD_PROPERTIES
#include "EmptyType.hpp"
using Armor = add_properties_ordered<
    Type,
    Naming,
    Protecting>;
#else

// struct Armor {
//     Name name;
//     Protection protection{};
// };

class Armor {
public:
    Name name;

    Armor(std::string name, Protection protection)
        : name{name}, protection{protection} {}

    auto& getProtection() noexcept {
        return protection;
    }

    const auto& getProtection() const noexcept {
        return protection;
    }

private:
    Protection protection;
};

#endif
