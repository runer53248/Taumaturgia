#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Usage/DefaultStrategies.hpp"
#include "Usage/With.hpp"

#include "Armor.hpp"
#include "Item.hpp"
#include "Player.hpp"
#include "Player_B.hpp"
#include "Weapon_A.hpp"
#include "Weapon_B.hpp"
#include "Weapon_C.hpp"

// MARK: main

int main() {
    Object weaponA = (From::base<Weapon_A> | WithUnordered::Damage)(
        Name{"Sword A"},
        Damage{1, Effect{EffectType::Infection}});
    Object weaponB = (From::base<Weapon_B> | WithUnordered::Damage)(
        Name{"Sword B"},
        Damage{5, Effect{EffectType::Infection}});
    Object weaponC = (From::base<Weapon_C> | WithUnordered::Damage)(
        Name{"Sword C"},
        Damage{50, Effect{EffectType::Infection}});

    // ! if Weapon_C was not Damagable then order of argument in c-tor will be different
    Object weapon_c2 = (From::base<Weapon_C> | WithUnordered::Health | WithUnordered::Damage)(
        Name{"Sword 2"},
        Health{100},
        Damage{10, Effect{
                       EffectType::Bleed,
                       Duration{5, DurationType::Round},
                       EffectState::Active}});

    Object paladin = (From::base<Player> | WithUnordered::Health | WithUnordered::EffectTypeContainer | WithUnordered::CureHealth)(
        Name{"Paladin"},
        Health{100},
        EffectType::Infection,
        CureHealth{10});  // will ignore Infection effects

    Object warior = (From::base<Player_B> | WithUnordered::Health)(
        Name{"Warior"},
        Health{100});

    Object potion = (From::base<Item> | WithUnordered::EffectTypeContainer)(
        Name{"Potion"},
        EffectType::Stun);

    Object shield = Armor(
        Name{"Shield"},
        ArmorClass{
            4,
            BodyLocation::Arms,
            {EffectType::Bleed}});

    Object chaimail = Armor{
        Name{"Chaimail"},
        ArmorClass{
            8,
            BodyLocation::Body,
            {EffectType::Daze}}};

    Object shield_2 = Armor{
        Name{"Shield 2"},
        ArmorClass{
            6,
            BodyLocation::Arms,
            {EffectType::Burn}}};

    auto print_info = [](auto& obj) {
        std::cout << obj.name() << " ";
        getOpt<Properties::Health, const Object>(obj)
            .and_then(print_hp);
        getOpt<Properties::Protection>(obj)
            .and_then(print_protection);
        getOpt<Properties::Wear>(obj)
            .and_then(print_wear);
        getOpt<Properties::Restore>(obj)
            .and_then(print_restore);
        std::cout << '\n';
    };

    std::cout << "print info:\n";
    print_info(paladin);
    std::cout << "\n";
    print_info(warior);
    std::cout << "\n";

    std::cout << "Warior wear armor:\n";
    defend(shield, &warior);
    defend(shield_2, &warior);
    defend(shield, &warior);
    defend(chaimail, &warior);
    print_info(warior);
    std::cout << "\n";

    auto attack_and_print_result = [&](auto& weapon, std::string_view text) {
        std::cout << text;
        print_object(weapon);
        attack(weapon, &weapon, &paladin);
        attack(weapon, &weapon, &warior);
        print_info(paladin);
        print_info(warior);
        std::cout << "\n";
    };

    attack_and_print_result(weaponA, "- weapon A attack both:\n");
    attack_and_print_result(weaponB, "- weapon B attack both:\n");
    attack_and_print_result(weaponC, "- weapon C attack both:\n");
    attack_and_print_result(weapon_c2, "- weapon C2 attack both:\n");

    std::cout << "Paladin restore from stun effect by potion use: \n";
    restore(potion, nullptr, &paladin);  // no owner needed by now
    print_info(paladin);
    std::cout << "\n";

    std::cout << "Paladin change shield: \n";
    getOpt<Properties::Wear>(paladin)
        .and_then([&](WearContainer& wear) {
            Protection& other_protection = getOpt<Properties::Protection>(shield_2).value().get();  // we now that it exist so don't check optional here

            auto opt_protection = wear.wearProtection(other_protection);  // change protection slot

            if (opt_protection) {
                std::cout << "Wear other armor: \n  ";  // TODO: get name of element (and add some ID)
                print_protection(std::ref(other_protection));
                std::cout << "\nin place of: \n  ";  // TODO: get name of element (and add some ID)
                print_protection(std::ref(opt_protection.value()));
                std::cout << '\n';
            }
            return std::optional{wear};
        });
    print_info(paladin);
    std::cout << "\n";

    std::cout << "Paladin remove all weared protection: \n";
    getOpt<Properties::Wear>(paladin)
        .and_then([&](WearContainer& wear) {  // remove all armor
            for (auto location : wear.getWearedLocations()) {
                auto opt_armor = wear.removeArmorAtLocation(location);
                if (opt_armor) {
                    std::cout << "remove armor:\n  ";  // TODO: get name of element (and add some ID)
                    print_protection(std::ref(opt_armor.value()));
                    std::cout << '\n';
                }
            }
            return std::optional{wear};
        });
    print_info(paladin);
    std::cout << '\n';

    for (const auto* entity : std::array{&paladin, &warior, &shield, &weaponA, &weaponB, &weaponC, &weapon_c2, &potion}) {
        print_properties(*entity);
        print_object(*entity);
    }
}
