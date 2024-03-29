#pragma once
#include "Object/DefaultStrategies.hpp"
#include "Examples/PreetyPrint/preety_print.hpp"

void attack(auto& backpack, auto& player, auto& enemy) {
    std::cout << "Items I can attack with:  //////////////////////////////\n\n";
    for (const auto& item : backpack) {
        if (not item.can_attack) {
            continue;
        }
        std::cout << player.name() << " attack " << enemy.name() << " with " << item.name() << ' ';
        getOpt<Parameter::Damage>(item)
            .and_then(print_dmg)
            .and_then(print_new_line);

        auto status = item.attack(&player, &enemy);
        std::cout << " - attack" << status << ": ";
        print_person(enemy);
        std::cout << '\n';
    }
}

void wear(auto& backpack, auto& player) {
    std::cout << "Items I can wear on:  //////////////////////////////\n";
    std::cout << "(armor protection protect against effect from attack)\n";
    std::cout << "(armor protection don't protect against ongoing effect)\n\n";
    for (const auto& item : backpack) {
        if (not item.can_wear) {
            continue;
        }
        auto status = item.wear(&player /*, &player*/);
        std::cout << " - wearing " << status << ": ";  // when target dont have Wearingable property
        if (status != ActionStatus::Success) {
            std::cout << player.name() << " can't wear " << item.name() << ' ';
            std::cout << '\n';
            continue;
        }

        std::cout << player.name() << " wear " << item.name();
        getOpt<Parameter::Wear>(item)
            .and_then(print_wear)
            .and_then(print_new_line);
        print_person(player);
        std::cout << '\n';
    }
}

void defend(auto& backpack, auto& player) {
    std::cout << "Items I can defend with:  //////////////////////////////\n\n";
    for (const auto& item : backpack) {
        if (not item.can_defend) {
            continue;
        }
        auto status = item.defend(&player /*, &player*/);
        std::cout << " - defending " << status << ": ";  // when target dont have Wearingable property
        if (status != ActionStatus::Success) {
            std::cout << player.name() << " can't defend with " << item.name() << ' ';
            std::cout << '\n';
            continue;
        }

        std::cout << player.name() << " defend with " << item.name();
        getOpt<Parameter::Protection>(item)
            .and_then(print_protection)
            .and_then(print_new_line);
        print_person(player);
        std::cout << '\n';
    }
}

void enemy_defend(auto& backpack, auto& enemy) {
    std::cout << "Items enemy try wear on:  //////////////////////////////\n";
    std::cout << "(enemy don't have wearingable property)\n\n";

    for (const auto& item : backpack) {
        if (not item.can_defend) {
            continue;
        }
        auto status = item.defend(&enemy /*, &player*/);
        std::cout << " - defending " << status << ": ";  // when target dont have Wearingable property
        if (status != ActionStatus::Success) {
            std::cout << enemy.name() << " can't defend with " << item.name() << ' ';
            std::cout << '\n';
            continue;
        }

        std::cout << enemy.name() << " defend with " << item.name() << ' ';
        getOpt<Parameter::Protection>(item)
            .and_then(print_protection)
            .and_then(print_new_line);
        print_person(enemy);
        std::cout << '\n';
    }
}

void restore(auto& backpack, auto& player) {
    std::cout << "Items I can restore with:  //////////////////////////////\n\n";
    for (const auto& item : backpack) {
        if (not item.can_restore) {
            continue;
        }
        auto status = item.restore(&player, &player);
        std::cout << " - restore" << status << ": ";

        std::cout << player.name() << " restore self with " << item.name() << ' ';
        // get(item, Parameter::Restore).and_then(print_restore);
        getOpt<Parameter::Restore>(item)
            .and_then(print_restore)
            .and_then(print_new_line);
        print_person(player);
        std::cout << '\n';
    }
}

void heal(auto& backpack, auto& player) {
    std::cout << "Items I can heal with:  //////////////////////////////\n\n";
    for (const auto& item : backpack) {
        if (not item.can_heal) {
            continue;
        }
        auto status = item.heal(&player, &player);
        std::cout << " - healing" << status << ": ";

        std::cout << player.name() << " heal self with " << item.name();
        if (auto cureHealth_opt = getOpt<Parameter::CureHealth>(item)) {
            const CureHealth& cureHealth = cureHealth_opt.value();
            std::cout << " for " << cureHealth.value() << toString(cureHealth.valueType()) << " Health";
        }
        std::cout << '\n';
        print_person(player);
        std::cout << '\n';
    }
}
