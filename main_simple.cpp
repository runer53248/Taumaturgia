#include <vector>
#include "Object/DefaultStrategies.hpp"
#include "Object/Object.hpp"
#include "Object/Properties/Properties.hpp"
#include "preety_print.hpp"

struct Item {
    std::string name;
};

struct Armor {
    Name name;
    Protection protection;
};

struct Weapon {
    std::string name;
};

struct Player {
    std::string name;
    ProtectionContainer armorWear{10};
};

int main() {
    std::vector<Object> container;

    Object weapon = Damaging<Weapon>{Name{"Sword"}, Damage{50, Effect{EffectType::Infection}}};
    Object weapon_2 = Damaging<Weapon>{Name{"Sword 2"}, Damage{50, Effect{EffectType::Stun, Duration(5, DurationType::Round), State{EffectState::Active}}}};
    Object paladin = Living<Restoring<Healing<Player>>>{Name{"Paladin"}, Health{100}, EffectType::Infection, Health{10}};  // will ignore Infection effects
    Object potion = Restoring<Item>{Name{"Potion"}, EffectType::Stun};
    Object shield = Armor{Name{"Shield"}, ArmorClass{4, BodyLocation::Arms, {EffectType::Bleed}}};                         // will protect against Bleed effects
    Object chaimail = Armor{Name{"Chaimail"}, ArmorClass{8, BodyLocation::Body, {EffectType::Daze}}};                      // will protect against Daze effects
    Armor{Name{"Chaimail"}, ArmorClass{8, BodyLocation::Body, {EffectType::Daze}}};
    Object shield_2 = Armor{Name{"Shield 2"}, ArmorClass{6, BodyLocation::Arms, {EffectType::Burn}}};                      // will protect against Burn effects

    container.push_back(Item{});

    auto print_hp2 = [](auto& obj) {
        getOpt<Parameter::Health, const Object>(obj).and_then(print_hp);
        getOpt<Parameter::Protection>(obj).and_then(print_protection);
        getOpt<Parameter::Wear>(obj).and_then(print_wear);
        std::cout << '\n';
    };

    print_hp2(paladin);

    shield.defend(&paladin);
    shield_2.defend(&paladin);
    shield.defend(&paladin);
    chaimail.defend(&paladin);
    print_hp2(paladin);

    weapon.attack(&weapon, &paladin);  // weapon is the owner of self
    print_hp2(paladin);

    weapon_2.attack(&paladin);  // owner is also target
    print_hp2(paladin);

    std::cout << "\nrestore from stun effect by potion use: \n";
    potion.restore(nullptr, &paladin);  // no owner needed by now
    print_hp2(paladin);

    getOpt<Parameter::Wear>(paladin).and_then([&](ProtectionContainer& wear) {
        auto& other_armor = getOpt<Parameter::Protection>(shield_2).value().get();  // we now that it exist so don't check optional here

        auto opt_armor = wear.wearProtection(other_armor);
        if (opt_armor) {
            std::cout << "wear other armor: ";  // TODO: get name of element (and add some ID)
            print_protection(std::ref(other_armor));
            std::cout << "\n  in place of: ";   // TODO: get name of element (and add some ID)
            print_protection(std::ref(opt_armor.value()));
            std::cout << '\n';
        }
        return std::optional{true};
    });
    print_hp2(paladin);

    getOpt<Parameter::Wear>(paladin).and_then([&](ProtectionContainer& wear) {  // remove all armor
        for (auto location : wear.getWearedLocations()) {
            auto opt_armor = wear.removeArmorAtLocation(location);
            if (opt_armor) {
                std::cout << "remove armor: ";  // TODO: get name of element (and add some ID)
                print_protection(std::ref(opt_armor.value()));
                std::cout << '\n';
            }
        }
        return std::optional{true};
    });
    print_hp2(paladin);
    std::cout << '\n';

    print_object_properties(paladin);
    print_object(paladin);

    print_object_properties(shield);
    print_object(shield);

    print_object_properties(weapon);
    print_object(weapon);

    print_object(weapon_2);

    print_object(potion);
}
