#pragma once
#include "Taumaturgia/Types/Name.hpp"
#include "Taumaturgia/Types/Protection.hpp"

// struct Armor {
//     Name name;
//     Protection protection{};
// };

struct Armor {
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
