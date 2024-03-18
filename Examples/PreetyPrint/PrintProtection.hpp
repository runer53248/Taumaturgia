#pragma once
#include <iostream>
#include "Object/Concepts/Types/ArmorClass.hpp"
#include "Object/Concepts/Types/Protection.hpp"
#include "PrintBodyLocation.hpp"
#include "PrintEffectType.hpp"

template <typename T>
    requires(std::same_as<T, ArmorClass> or std::same_as<T, Protection>)
constexpr auto& operator<<(std::ostream& out, const T& armorClass) {
    auto ac = armorClass.armorClass();
    auto location = armorClass.location();
    auto effects = armorClass.protectEffects();

    return print_in_round_braces(
        out, "Ac",
        [&] {
            out << ac << " on " << location;
            if (effects.empty()) {
                return;
            }
            out << ' ';
            print_in_round_braces(
                out, "protections",
                [&] {
                    out << effects;
                });
        });
}
