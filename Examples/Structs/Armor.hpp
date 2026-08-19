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
    Armor_Class() = default;

    Armor_Class(std::string name, Protection protection)
        : name{name}, protection{protection} {}

    auto& getProtection() noexcept {
        return protection;
    }

    const auto& getProtection() const noexcept {
        return protection;
    }

    //* for parse_type_name function to deduce types

    template <size_t S = 0, typename Self>
        requires(S < 2)
    decltype(auto) getType(this Self&& self) {
        if constexpr (S == 0) {
            return (self.protection);
        } else {
            return (self.name);
        }
    }

    template <size_t S = 0, typename Self>
    decltype(auto) getType(this Self&& self) = delete;

    property_t<Naming> name{};

private:
    property_t<Protecting> protection{};
};

#ifdef WITH_ADD_PROPERTIES
#define USES_ADD_PROPERTIES
using Armor = ArmorBuild;
#else
using Armor = Armor_Class;
#endif
