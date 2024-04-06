#pragma once
#include <iostream>
#include "Taumaturgia/Concepts/Types/WearContainer.hpp"
#include "PrintProtection.hpp"

auto& operator<<(std::ostream& out, const WearContainer& armorWear) {
    auto full_ac = armorWear.value();
    auto full_effects = armorWear.protectEffects();
    const auto armorLocations = armorWear.getWearedLocations();

    print_in_round_braces(
        out, "armor class",
        [&] {
            out << full_ac;
            if (full_effects.empty()) {
                return;
            }
            out << ' ';
            print_in_round_braces(
                out, "protections",
                [&] {
                    out << full_effects;
                });
        });

    if (armorLocations.empty()) {
        return out;
    }

    out << "\n\t";
    for (auto location : armorLocations) {
        if (auto opt = armorWear.armorAtLocation(location)) {
            const Protection& protection = opt.value();
            out << protection << ' ';
        }
    }
    return out;
}
