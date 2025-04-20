#pragma once
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Usage/DefaultStrategies.hpp"

// MARK: attack

void attack(auto& backpack, auto& player, auto& enemy) {
    std::cout << "Items I can attack with:  //////////////////////////////\n\n";
    for (const Object& item : backpack) {
        if (not item.hasStrategyFor(Properties::Damage)) {
            continue;
        }
        std::cout << player.name() << " attack " << enemy.name() << " with " << item.name() << ' ';
        // use getOpt template method of Object 
        item.getOpt<Properties::Damage>()
            .and_then(print_dmg)
            .and_then(print_new_line);

        auto status = attack(item, &player, &enemy);
        std::cout << " - attack" << status << ": ";
        print_person(enemy);
        std::cout << '\n';
    }
}

// MARK: wear

void wear(std::ranges::range auto& backpack, auto& player) {
    std::cout << "Items I can wear on:  //////////////////////////////\n";
    std::cout << "(armor protection protect against effect from attack)\n";
    std::cout << "(armor protection don't protect against ongoing effect)\n\n";
    for (const auto& item : backpack) {
        if (not item.hasStrategyFor(Properties::Wear)) {
            continue;
        }
        auto status = wear(item, &player /*, &player*/);
        std::cout << " - wearing " << status << ": ";  // when target dont have Wearingable property
        if (status != ActionStatus::Success) {
            std::cout << player.name() << " can't wear " << item.name() << ' ';
            std::cout << '\n';
            continue;
        }

        std::cout << player.name() << " wear " << item.name();
        // use getOpt template method of auto type 
        item.template getOpt<Properties::Wear>()
            .and_then(print_wear)
            .and_then(print_new_line);
        print_person(player);
        std::cout << '\n';
    }
}

// MARK: defend

void defend(std::ranges::range auto& backpack, auto& player) {
    std::cout << "Items I can defend with:  //////////////////////////////\n\n";
    for (const auto& item : backpack) {
        if (not item.hasStrategyFor(Properties::Protection)) {
            continue;
        }
        auto status = defend(item, &player /*, &player*/);
        std::cout << " - defending " << status << ": ";  // when target dont have Wearingable property
        if (status != ActionStatus::Success) {
            std::cout << player.name() << " can't defend with " << item.name() << ' ';
            std::cout << '\n';
            continue;
        }

        std::cout << player.name() << " defend with " << item.name();
        getOpt<Properties::Protection>(item)
            .and_then(print_protection)
            .and_then(print_new_line);
        print_person(player);
        std::cout << '\n';
    }
}

// MARK: enemy_defend

void enemy_defend(std::ranges::range auto& backpack, auto& enemy) {
    std::cout << "Items enemy try wear on:  //////////////////////////////\n";
    std::cout << "(enemy don't have wearingable property)\n\n";

    for (const auto& item : backpack) {
        if (not item.hasStrategyFor(Properties::Protection)) {
            continue;
        }
        auto status = defend(item, &enemy /*, &player*/);
        std::cout << " - defending " << status << ": ";  // when target dont have Wearingable property
        if (status != ActionStatus::Success) {
            std::cout << enemy.name() << " can't defend with " << item.name() << ' ';
            std::cout << '\n';
            continue;
        }

        std::cout << enemy.name() << " defend with " << item.name() << ' ';
        getOpt<Properties::Protection>(item)
            .and_then(print_protection)
            .and_then(print_new_line);
        print_person(enemy);
        std::cout << '\n';
    }
}

// MARK: restore

void restore(std::ranges::range auto& backpack, auto& player) {
    std::cout << "Items I can restore with:  //////////////////////////////\n\n";
    for (const auto& item : backpack) {
        if (not item.hasStrategyFor(Properties::Restore) ) {
            continue;
        }
        auto status = restore(item, &player, &player);
        std::cout << " - restore" << status << ": ";

        std::cout << player.name() << " restore self with " << item.name() << ' ';
        // get(item, Properties::Restore).and_then(print_restore);
        getOpt<Properties::Restore>(item)
            .and_then(print_restore)
            .and_then(print_new_line);
        print_person(player);
        std::cout << '\n';
    }
}

// MARK: heal

void heal(std::ranges::range auto& backpack, auto& player) {
    std::cout << "Items I can heal with:  //////////////////////////////\n\n";
    for (const auto& item : backpack) {
        if (not item.hasStrategyFor(Properties::CureHealth)) {
            continue;
        }
        auto status = heal(item, &player, &player);
        std::cout << " - healing" << status << ": ";

        std::cout << player.name() << " heal self with " << item.name();
        if (auto cureHealth_opt = getOpt<Properties::CureHealth>(item)) {
            const CureHealth& cureHealth = cureHealth_opt.value();
            std::cout << " for " << cureHealth.value() << toString(cureHealth.valueType()) << " Health";
        }
        std::cout << '\n';
        print_person(player);
        std::cout << '\n';
    }
}
