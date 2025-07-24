#pragma once

// MARK: Armor

class Armor {
public:
    Name name;

    Armor(std::string name, Protection protection)
        : name{name}, protection{protection} {}

    auto& getProtection() { return protection; }
    const auto& getProtection() const { return protection; }

private:
    Protection protection;
};
