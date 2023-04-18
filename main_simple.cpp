#include <vector>
#include "Object/DefaultStrategies.hpp"
#include "Object/Object.hpp"
#include "Object/Properties/Properties.hpp"
#include "preety_print.hpp"

/*actions 5
    attack
    defend
    heal
    restore
    get
*/

/*Enums 5
    BodyLocation
    DurationType
    EffectState
    EffectType
    Parameter
*/

/*types
    ArmorClass
        //enum BodyLocation
        //Effect
    Damage
        Effect
            Duration
                //enum DurationType
            State
                //enum EffectState
            //enum EffectType
    Health
        EffectContainer
    EffectTypeContainer * // aka RestoreList
    Name
    VariantType
*/

/*parameters
    Health
    CureHealth
    Armor
    Damage
    Restore
    Wear
*/

/*Properties
    Damaging
    Healing
    Living
    Naming
    Protecting
    Restoring
*/

struct Item {
    std::string name;
};

struct Armor {
    Name name;
    ArmorClass ac;
};

struct Weapon {
    std::string name;
};

struct Player {
    std::string name;
    // ArmorClass ac{10, BodyLocation::ALL}; // old functionality to remove
    ArmorClassContainer armorWear{10};
};

int main() {
    std::vector<Object> container;

    Object weapon = Damaging<Weapon>{Name{"Sword"}, Damage{50, Effect{EffectType::Infection}}};
    Object weapon_2 = Damaging<Weapon>{Name{"Sword 2"}, Damage{50, Effect{EffectType::Stun, Duration(5, DurationType::Round), State{EffectState::Active}}}};
    Object paladin = Living<Restoring<Healing<Player>>>{Name{"Paladin"}, Health{100}, EffectType::Infection, Health{10}};  // will ignore Infection effects
    Object potion = Restoring<Item>{Name{"Potion"}, EffectType::Stun};
    Object shield = Armor{Name{"Shield"}, ArmorClass{4, BodyLocation::Arms, {EffectType::Bleed}}};     // will protect against Bleed effects
    Object chaimail = Armor{Name{"Chaimail"}, ArmorClass{8, BodyLocation::Body, {EffectType::Daze}}};  // will protect against Bleed effects
    Object shield_2 = Armor{Name{"Shield 2"}, ArmorClass{6, BodyLocation::Arms, {EffectType::Burn}}};  // will protect against Bleed effects

    container.push_back(Item{});

    auto print_hp2 = [](auto& obj) {
        getOpt<Parameter::Health, const Object>(obj).and_then(print_hp);
        getOpt<Parameter::Armor>(obj).and_then(print_ac);
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

    getOpt<Parameter::Wear>(paladin).and_then([&](ArmorClassContainer& wear) {
        ArmorClass& other_armor = getOpt<Parameter::Armor>(shield_2).value();  // we now that it exist so don't check optional here

        auto opt_armor = wear.wearArmor(other_armor);
        if (opt_armor) {
            std::cout << "wear other armor: ";  // TODO: get name of element (and add some ID)
            print_ac(std::ref(other_armor));
            std::cout << "\n  in place of: ";  // TODO: get name of element (and add some ID)
            print_ac(std::ref(opt_armor.value()));
            std::cout << '\n';
        }
        return std::optional{true};
    });
    print_hp2(paladin);

    getOpt<Parameter::Wear>(paladin).and_then([&](ArmorClassContainer& wear) {  // remove all armor
        for (auto location : wear.getWearedLocations()) {
            auto opt_armor = wear.removeArmorAtLocation(location);
            if (opt_armor) {
                std::cout << "remove armor: ";  // TODO: get name of element (and add some ID)
                print_ac(std::ref(opt_armor.value()));
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
