

void attack(auto& backpack, auto& player, auto& enemy) {
    std::cout << "Items I can attack with:  //////////////////////////////\n\n";
    for (const auto& item : backpack) {
        if (not item.can_attack) {
            continue;
        }
        std::cout << player.name() << " attack " << enemy.name() << " with " << item.name();
        getOpt<Parameter::Damage>(item)
            .and_then(print_dmg);
        std::cout << '\n';
        if (not item.attack(&player, &enemy)) {
            std::cout << " attack miss ";  // unusable yet
        }
        print_person(enemy);
    }
    std::cout << '\n';
}

void defend(auto& backpack, auto& player) {
    std::cout << "Items I can defend with:  //////////////////////////////\n";
    std::cout << "(armor protection don't restore ongoing effect - need to use correct restore or have both restore and living properties as target of attack)\n\n";
    for (const auto& item : backpack) {
        if (not item.can_defend) {
            continue;
        }
        if (not item.defend(&player /*, &player*/)) {
            std::cout << " protection broken\n";  // when target dont have Wearingable property
            std::cout << player.name() << " can't defend self with " << item.name();
            std::cout << '\n';
            continue;
        }

        std::cout << player.name() << " defend self with " << item.name();
        getOpt<Parameter::Protection>(item)
            .and_then(print_protection);
        std::cout << '\n';
        print_person(player);
    }
    std::cout << '\n';
}

void enemy_defend(auto& backpack, auto& enemy) {
    std::cout << "Items enemy try defend with:  //////////////////////////////\n";
    std::cout << "(enemy don't have wearingable property)\n\n";

    for (const auto& item : backpack) {
        if (not item.can_defend) {
            continue;
        }
        if (not item.defend(&enemy /*, &player*/)) {
            std::cout << " protection broken\n";  // when target dont have Wearingable property
            std::cout << enemy.name() << " can't defend self with " << item.name();
            std::cout << '\n';
            continue;
        }

        std::cout << enemy.name() << " defend self with " << item.name();
        getOpt<Parameter::Protection>(item)
            .and_then(print_protection);
        std::cout << '\n';
        print_person(enemy);
    }
    std::cout << '\n';
}

void restore(auto& backpack, auto& player) {
    std::cout << "Items I can restore with:  //////////////////////////////\n\n";
    for (const auto& item : backpack) {
        if (not item.can_restore) {
            continue;
        }
        if (not item.restore(&player, &player)) {
            std::cout << " restoration don't work ";  // unusable yet
        }

        std::cout << player.name() << " restore self with " << item.name();
        // get(item, Parameter::Restore).and_then(print_restore);
        getOpt<Parameter::Restore>(item)
            .and_then(print_restore);  // same
        std::cout << '\n';
        print_person(player);
    }
    std::cout << '\n';
}

void heal(auto& backpack, auto& player) {
    std::cout << "Items I can heal with:  //////////////////////////////\n\n";
    for (const auto& item : backpack) {
        if (not item.can_heal) {
            continue;
        }
        if (not item.heal(&player, &player)) {
            std::cout << " healing don't work ";  // unusable yet
        }

        std::cout << player.name() << " heal self with " << item.name();
        if (auto cureHealth_opt = getOpt<Parameter::CureHealth>(item)) {
            const Health& cureHealth = cureHealth_opt.value();
            std::cout << " for " << cureHealth.value() << " Health";
        }
        std::cout << '\n';
        print_person(player);
    }
    std::cout << "\n";
}
